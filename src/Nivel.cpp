#include "../headers/Nivel.h"
#include <utility>
#include <functional>
#include <chrono>
#include "IntrebareRaspunsLiber.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

void afiseazaDashboardNivel(const std::string& numeNivel, int vieti, size_t scor, const std::string& textIntrebare) {
    using namespace ftxui;

    std::string inimi;
    for (int i = 0; i < 5; ++i) inimi += (i < vieti) ? " ❤️ " : " 🖤 ";

    auto dashboard = vbox({
        hbox({
            text("  " + numeNivel) | bold | color(Color::Cyan),
            filler(),
            text(" SCOR GLOBAL: " + std::to_string(scor)) | bold | color(Color::Yellow),
        }) | border,

        separator(),

        vbox({
            filler(),
            text(textIntrebare) | hcenter | bold,
            filler(),
        }) | size(HEIGHT, EQUAL, 5) | borderDouble | color(Color::White),

        hbox({
            text(" VIETI: "),
            text(inimi),
            filler()
        })
    }) ;

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(dashboard));
    Render(screen, dashboard);

    std::cout << "\033[2J\033[H" << std::flush;
    std::cout << screen.ToString() << std::endl;
}


void afiseazaPovesteGrafic(const std::string& titlu, const std::string& continut) {
    using namespace ftxui;

    auto poveste_render = vbox({
        text(" 📖 CAPITOL DEBLOCAT: " + titlu) | bold | color(Color::Yellow) | center,
        separator(),
        paragraph(continut) | color(Color::White),
        separator(),
        text(" Apasa ENTER pentru a merge mai departe ") | dim | hcenter
    }) | borderDouble | color(Color::Yellow) | size(WIDTH, EQUAL, 80) | center;

    auto document = vbox({
        filler(),
        poveste_render,
        filler(),
    });

    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    Render(screen, document);

    std::cout << "\033[2J\033[H" << std::flush;
    std::cout << screen.ToString() << std::endl;

    std::cin.get();
}

Nivel::Nivel(const std::string &nume, std::vector<std::unique_ptr<Intrebare> > intrebari_,
             const CapitolPoveste &poveste_)
    : nivelPromovat{false} {
    this->numeNivel = nume;
    this->intrebari = std::move(intrebari_);
    this->poveste = poveste_;
}

Nivel::Nivel(const Nivel &nivel)
    : numeNivel(nivel.numeNivel),
      poveste(nivel.poveste),
      nivelPromovat(nivel.nivelPromovat) {
    ///std::cout << "Nivel " << nivel.numeNivel << " copiat.\n";
    for (const std::unique_ptr<Intrebare> &intrebare_ptr: nivel.intrebari) {
        this->intrebari.push_back(intrebare_ptr->clone());
    }
}

Nivel &Nivel::operator=(const Nivel &nivel) {

    if (this != &nivel) {
        Nivel copie = nivel;

        ///swap de resurse - pt a evita scrierea de doua ori a codului de copiere
        std::swap(numeNivel, copie.numeNivel);
        std::swap(intrebari, copie.intrebari);
        std::swap(poveste, copie.poveste);
        std::swap(nivelPromovat, copie.nivelPromovat);
    }
    return *this;
}

//
// void Nivel::afiseazaVieti(int count, size_t scor) const {
//
//     std::cout << "  Vieti Ramase:   ";
//
//     for (int v = 0; v < 5; v++)
//         if (v < count)
//             std::cout << "# ";
//         else
//             std::cout << "- ";
//
//     std::cout << "\n";
//     std::cout << "  Scorul Curent:      " << scor << "\n";
// };


bool Nivel::ruleazaTest(size_t &scorGlobal, StatisticiJoc &stats) {
    size_t raspunsuriCorecte = 0;
    int vietiRamase = 5;

    std::cout << "\n " << numeNivel << " \n";
    std::cout << "Raspunde corect la fiecare intrebare pentru a continua!\n";

    for (size_t i = 0; i < intrebari.size(); i++) {
        Intrebare *intrebare = intrebari[i].get();
        bool corect = false;
        std::cout << "\n[HINT]: Analizeaza cu atentie cerinta!";

        ///idenfiticam tipul de intrebare - daca e raspuns liber
        const IntrebareRaspunsLiber *liberPtr = dynamic_cast<IntrebareRaspunsLiber *>(intrebare);

        while (!corect && vietiRamase > 0) {
            auto timpStart = std::chrono::steady_clock::now();

            afiseazaDashboardNivel(numeNivel, vietiRamase, scorGlobal, intrebare->getText());
            std::cout << "\n" << *intrebare;

            if (liberPtr) {
                ///raspuns liber - citim stringul
                std::string raspunsUtilizatorStr;
                std::cout << "Raspunsul tau (text): ";

                std::getline(std::cin >> std::ws, raspunsUtilizatorStr);

                if (intrebare->verificaRaspunsText(raspunsUtilizatorStr)) {
                    auto timpFinal = std::chrono::steady_clock::now();
                    auto durata = std::chrono::duration_cast<std::chrono::milliseconds>(timpFinal - timpStart).count();
                    if (durata < 5000) {
                        ///mai putin de 5s
                        scorGlobal += 5;
                        std::cout << "BONUS VITEZA! + 5 puncte.\n";
                    }

                    std::cout << "Raspuns CORECT! Ai castigat " << intrebare->calculeazaPunctaj() << " puncte.\n";
                    scorGlobal += intrebare->calculeazaPunctaj();
                    raspunsuriCorecte++;
                    corect = true;
                    stats.adaugaRaspuns(true);
                } else {
                    vietiRamase--;
                    if (scorGlobal >= 1)
                        scorGlobal--;
                    else scorGlobal = 0; ///scorul ramane >=0 si scadem 1 dc e gresit rasp

                    std::cout << "\n Raspuns GRESIT! Ai pierdut 1 punct si 1 viata.\n";
                    if (vietiRamase == 0) {
                        std::cout << " JOC TERMINAT! Ai ramas fara vieti! \n";
                        return false; ///inchidem jocul
                    }
                    std::cout << "Incearca din nou.\n";
                    stats.adaugaRaspuns(false);
                }
            } else {
                ///altfel citim int
                int raspunsUtilizatorInt;
                std::cout << "Raspunsul tau (nr optiune): ";

                if (!(std::cin >> raspunsUtilizatorInt)) {
                    ///erori
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nIntrare invalida. Te rog introdu numarul optiunii.\n";
                    continue;
                }

                if (intrebare->verificaRaspuns(raspunsUtilizatorInt)) {
                    std::cout << "Raspuns CORECT! Ai castigat " << intrebare->calculeazaPunctaj() << " puncte.\n";
                    scorGlobal += intrebare->calculeazaPunctaj();
                    stats.adaugaRaspuns(true);
                    raspunsuriCorecte++;
                    corect = true;
                } else {
                    vietiRamase--; ///pierde o viata
                    if (scorGlobal >= 1)
                        scorGlobal--;
                    else scorGlobal = 0; ///scorul ramane >=0 si scadem 1 dc e gresit rasp
                    std::cout << "\n Raspuns GRESIT! Ai pierdut 1 punct si 1 viata.\n";
                    if (vietiRamase == 0) {
                        std::cout << " JOC TERMINAT! Ai ramas fara vieti! \n";
                        return false; ///inchidem jocul
                    }
                    std::cout << "Incearca din nou.\n";
                    stats.adaugaRaspuns(false);
                }
                ///curatam buffer-ul
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (vietiRamase == 0)
                return false;
        }
    }

    if (raspunsuriCorecte == intrebari.size()) {
        this->poveste.deblocheaza();
        this->nivelPromovat = true;

        stats.bifeazaNivelTerminat();
        stats.bifeazaPovesteDescoperita();

        std::cout << "\n FELICITARI! Scorul tau total este: " << scorGlobal << ".\n";
        afiseazaPovesteGrafic(this->poveste.getTitlu(), this->poveste.getText());
    }
    return true;
}


///getter pt numeNivel
/*const std::string& Nivel::getNumeNivel() const {
    return numeNivel;
}*/

bool Nivel::estePromovat() const {
    return nivelPromovat;
}

///getter pentru a accesa un obiect Intrebare
/*const Intrebare& Nivel::getIntrebare(size_t i) const {
    ///verificam daca i este valid
    if (i >= intrebari.size()) {
        throw std::out_of_range("Index intrebare invalid.");
    }
    return *intrebari[i].get(); ///returnare referinta la ob intrebare
}*/

///getter pentru a accesa capitolul
/*const CapitolPoveste& Nivel::getCapitol() const {
    return poveste;
}
*/

std::ostream &operator<<(std::ostream &os, const Nivel &niv) {
    os << "\n=== Nivel " << niv.numeNivel << " ===\n";
    os << "Status: ";
    if (niv.nivelPromovat) os << "DEBLOCAT";
    else os << "NEDEBLOCAT";
    os << "\n";
    os << "Intrebari: " << niv.intrebari.size() << "\n";
    os << niv.poveste;
    return os;
}
