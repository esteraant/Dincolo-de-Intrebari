#include "Intrebare.h"
#include "CapitolPoveste.h"
#include "Nivel.h"
#include "Quiz.h"
#include "utils.h"
#include "aplicatie_exceptii.h"
#include "Clasament.h"
#include "ProfilUtilizator.h"
#include "ColectieResurse.h"
#include <ftxui/dom/table.hpp>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include <utility>


void meniuInteractiv(std::string& nume) {
    using namespace ftxui;
    auto screen = ScreenInteractive::TerminalOutput();

    int selected = 0;
    std::vector<std::string> entries = {" START AVENTURA ", " VEZI CLASAMENT ", " IESIRE "};

    auto input_nume = Input(&nume, "Scrie numele aici...");
    auto menu = Menu(&entries, &selected);

    bool nume_confirmat = false;
    bool vizualizare_clasament = false;

    auto component = Renderer(Container::Vertical({input_nume, menu}), [&] {
        if (vizualizare_clasament) {
            auto& scoruri = Clasament::getInstanta().getListaScoruri();
            std::vector<std::vector<Element>> date_tabel;
            date_tabel.push_back({text(" POZ ") | bold, text(" JUCATOR ") | bold, text(" SCOR ") | bold});

            for (size_t i = 0; i < scoruri.size(); ++i) {
                date_tabel.push_back({text(std::to_string(i + 1)), text(scoruri[i].nume), text(std::to_string(scoruri[i].valoare))});
            }

            auto tabel = Table(date_tabel);
            tabel.SelectAll().Separator(LIGHT);
            tabel.SelectRow(0).Decorate(color(Color::Cyan));

            return vbox({
                filler(),
                vbox({
                    text("  TOP SCORURI  ") | bold | color(Color::Yellow) | center,
                    separator(),
                    tabel.Render() | hcenter,
                    separator(),
                    text(" Apasa ENTER pentru a te intoarce la meniu ") | dim | hcenter
                }) | borderDouble | color(Color::Blue) | center,
                filler()
            });
        }

        if (!nume_confirmat) {
            return vbox({
                filler(),
                vbox({
                    text(" CUM TE NUMESTI? ") | bold | color(Color::Cyan) | center,
                    separator(),
                    input_nume->Render() | border | hcenter | size(WIDTH, EQUAL, 30),
                    separatorLight(),
                    text(" Apasa ENTER pentru a confirma ") | dim | hcenter
                }) | borderDouble | color(Color::Blue) | center,
                filler()
            });
        }

        return vbox({
            filler(),
            vbox({
                text(" BINE AI VENIT, " + nume + "! ") | bold | color(Color::Green) | center,
                separator(),
                menu->Render() | hcenter,
                separator(),
                text(" Foloseste sagetile si ENTER ") | dim | hcenter
            }) | borderDouble | color(Color::Blue) | center,
            filler()
        });
    });

    component |= CatchEvent([&](Event event) {
        if (event == Event::Return) {
            if (vizualizare_clasament) {
                vizualizare_clasament = false;
                return true;
            }
            if (!nume_confirmat && !nume.empty()) {
                nume_confirmat = true;
                return true;
            }
            if (nume_confirmat) {
                if (selected == 0) screen.Exit();
                if (selected == 1) {
                    vizualizare_clasament = true;
                    return true;
                }
                if (selected == 2) exit(0);
                return true;
            }
        }
        return false;
    });

    screen.Loop(component);
}


void afiseazaClasamentFT() {
    using namespace ftxui;

    auto& scoruri = Clasament::getInstanta().getListaScoruri();

    std::vector<std::vector<Element>> date_tabel;
    date_tabel.push_back({
        text(" POZ ") | bold | center,
        text(" EXPLORATOR ") | bold | center,
        text(" PUNCTAJ ") | bold | center
    });

    for (size_t i = 0; i < scoruri.size(); ++i) {
        date_tabel.push_back({
            text(std::to_string(i + 1)) | hcenter,
            text(scoruri[i].nume) | color(Color::Yellow) | hcenter,
            text(std::to_string(scoruri[i].valoare)) | bold | color(Color::Green) | hcenter
        });
    }

    auto tabel = Table(date_tabel);
    tabel.SelectAll().Separator(LIGHT);
    tabel.SelectRow(0).Decorate(color(Color::Cyan));
    tabel.SelectRow(0).Separator(DOUBLE);

    auto document = vbox({
        text(" CLASAMENT ") | bold | center | color(Color::Yellow),
        tabel.Render() | center,
        text(" Felicitari tuturor participantilor! ") | dim | center
    }) | borderDouble | color(Color::Blue) | center;

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);
    std::cout << "\n" << screen.ToString() << std::endl;
}

int main() {
    std::cout << "\033[2J\033[H" << std::flush;
    std::vector<std::unique_ptr<Intrebare> > toateIntrebarile;

    ColectieResurse<CapitolPoveste> bibliotecaCapitole;
    ColectieResurse<Nivel> structuraNivele;

    try {

        toateIntrebarile = citesteIntrebari("intrebari.txt");
        auto vectorCapitole = citestePovesti("poveste.txt");
        for (auto& cap : vectorCapitole) {
            bibliotecaCapitole.adauga(std::move(cap));
        }

        constexpr size_t minIntrebari = 8;
        constexpr size_t minCapitole = 4;

        if (toateIntrebarile.size() < minIntrebari || bibliotecaCapitole.getDimensiune() < minCapitole)
            throw EroareDateInsuficiente(minIntrebari, toateIntrebarile.size());
    }
    catch (const EroareFisierInexistent &e) {
        std::cerr << "\n [CRITICAL]: Lipseste o resursa vitala!\n";
        std::cerr << " Mesaj: " << e.what() << "\n";
        return 1;
    }
    catch (const EroareFormatDate &e) {
        std::cerr << "\n [FORMAT ERROR]: Verificati continutul fisierelor .txt.\n";
        std::cerr << " Detalii: " << e.what() << "\n";
        return 1;
    }
    catch (const EroareDateInsuficiente &e) {
        std::cerr << "\n [LOGIC ERROR]: Continut insuficient pentru Quiz.\n";
        std::cerr << " Detalii: " << e.what() << "\n";
        return 1;
    }

    catch (const AplicatieExceptie &e) {
        std::cout << "\n    EROARE LA INCARCAREA DATELOR    \n";
        std::cout << "DETALII: " << e.what() << "\n";
        std::cout << "Aplicatia nu poate continua. Va rugam verificati fisierele de intrare.\n";
        return 1;
    }
    catch (const std::exception &e) {
        std::cout << "\n    EROARE NECUNOSCUTA APLICATIE \n";
        std::cout << "DETALII: " << e.what() << "\n";
        return 1;
    }

    ///crearea de nivele
        ///nivelul 1
    std::vector<std::unique_ptr<Intrebare> > intrebariN1;
    intrebariN1.push_back(std::move(toateIntrebarile[0]));
    intrebariN1.push_back(std::move(toateIntrebarile[1]));
    structuraNivele.adauga(Nivel("Nivelul 1", std::move(intrebariN1), bibliotecaCapitole[0]));

    ///nivelul 2
    std::vector<std::unique_ptr<Intrebare> > intrebariN2;
    intrebariN2.push_back(std::move(toateIntrebarile[2]));
    intrebariN2.push_back(std::move(toateIntrebarile[3]));
    structuraNivele.adauga(Nivel("Nivelul 2", std::move(intrebariN2), bibliotecaCapitole[1]));

    ///nivelul 3
    std::vector<std::unique_ptr<Intrebare> > intrebariN3;
    intrebariN3.push_back(std::move(toateIntrebarile[4]));
    intrebariN3.push_back(std::move(toateIntrebarile[5]));
    structuraNivele.adauga(Nivel("Nivelul 3", std::move(intrebariN3), bibliotecaCapitole[2]));

    ///nivelul 4
    std::vector<std::unique_ptr<Intrebare> > intrebariN4;
    intrebariN4.push_back(std::move(toateIntrebarile[6]));
    intrebariN4.push_back(std::move(toateIntrebarile[7]));
    structuraNivele.adauga(Nivel("Nivelul 4", std::move(intrebariN4), bibliotecaCapitole[3]));


    try {
        Clasament::getInstanta().incarca();
    } catch (const std::exception &e) {
        std::cerr << "Eroare la incarcarea clasamentului: " << e.what() << "\n";
    }

    std::string numeUtilizator;

    // std::cout << "Introdu un nume de utilizator: ";
    // if (!(std::cin >> numeUtilizator)) {
    //     numeUtilizator = "Anonim";
    // }
    meniuInteractiv(numeUtilizator);

    ProfilUtilizator profil(numeUtilizator);
    profil.incarca(); //incarca highscore-ul anterior

    std::cout << "\n\n";
    std::cout << "Profil incarcat pentru utilizatorul: " << profil.getNumeProfil() << "\n";
    std::cout << "Highscore-ul tau anterior este: "
            << profil.getHighscoreGlobal() << " puncte.\n\n";
    ///mutarea vectorului de nivele in Quiz
    std::vector<Nivel> vectorPtQuiz;
    for(size_t i = 0; i < structuraNivele.getDimensiune(); ++i) {
        vectorPtQuiz.push_back(structuraNivele[i]);
    }

    Quiz quiz(numeUtilizator, std::move(vectorPtQuiz));
    quiz.aplicatie();
    std::cout << quiz;

    size_t scorFinal = quiz.getScorTotal();

    profil.actualizeazaHighscore(scorFinal);

    //actualizare clasament global
    Clasament::getInstanta().adaugaScor(numeUtilizator, scorFinal);
    Clasament::getInstanta().salveazaJson();
    afiseazaClasamentFT();


    ///testare
    //std::cout << "\n Testare Getters si Polimorfism \n";
    //if (quiz.get_nivele().size() > 0) {
        /*const Intrebare& prima_intrebare = quiz.get_nivele()[0].getIntrebare(0);
        std::cout << "Titlu Intrebare: " << prima_intrebare.getText() << "\n";
        std::cout << "Punctaj: " << prima_intrebare.calculeazaPunctaj() << "\n";

        ///verificare dynamic_cast
        IntrebareGrila* grila_ptr = dynamic_cast<IntrebareGrila*>(const_cast<Intrebare*>(&prima_intrebare));
        if (grila_ptr)
                 std::cout << "Numar Optiuni (Grila): " << grila_ptr->getNumarOptiuni() << "\n";
        std::cout << "Titlu Capitol (Nivel 1): " << quiz.get_nivele()[0].getCapitol().getTitlu() << "\n";
        */
    //}

    quiz.getStatistici().afiseazaStatistici(static_cast<int>(structuraNivele.getDimensiune()));
    return 0;
}
