#include "../headers/Nivel.h"
#include <utility>
#include <functional>
//#include <stdexcept>
#include <chrono>
#include "IntrebareRaspunsLiber.h"
///constructor de initializare
Nivel::Nivel(const std::string &nume, std::vector<std::unique_ptr<Intrebare> > intrebari_,
             const CapitolPoveste &poveste_)
    : nivelPromovat{false} {
    this->numeNivel = nume;
    this->intrebari = std::move(intrebari_);
    this->poveste = poveste_;
}

///constructor de copiere
Nivel::Nivel(const Nivel &nivel)
    : numeNivel{nivel.numeNivel},
      poveste{nivel.poveste},
      nivelPromovat{nivel.nivelPromovat} {
    ///std::cout << "Nivel " << nivel.numeNivel << " copiat.\n";
    for (const std::unique_ptr<Intrebare> &intrebare_ptr: nivel.intrebari) {
        this->intrebari.push_back(intrebare_ptr->clone());
    }
}

///operator de atribuire
Nivel &Nivel::operator=(const Nivel &nivel) {
    ///std::cout << "Atribuire Nivel " << nivel.numeNivel << " \n";

    if (this != &nivel) {
        ///creeaza o copie
        Nivel copie = nivel;

        ///swap de resurse - pt a evita scrierea de doua ori a codului de copiere
        std::swap(numeNivel, copie.numeNivel);
        std::swap(intrebari, copie.intrebari);
        std::swap(poveste, copie.poveste);
        std::swap(nivelPromovat, copie.nivelPromovat);
    }
    return *this;
}


void Nivel::afiseazaVieti(int count, size_t scor) const {
    ///functie pt afisarea inimilor

    std::cout << "  Vieti Ramase:   ";

    for (int v = 0; v < 5; v++)
        if (v < count)
            std::cout << "# ";
        else
            std::cout << "- ";

    std::cout << "\n";
    std::cout << "  Scorul Curent:      " << scor << "\n";
};


bool Nivel::ruleazaTest(size_t &scorGlobal, StatisticiJoc &stats) {
    size_t raspunsuriCorecte = 0;
    int vietiRamase = 5;

    std::cout << "\n " << numeNivel << " \n";
    std::cout << "Raspunde corect la fiecare intrebare pentru a continua!\n";

    for (size_t i = 0; i < intrebari.size(); i++) {
        Intrebare *intrebare = intrebari[i].get();
        bool corect = false;

        ///idenfiticam tipul de intrebare - daca e raspuns liber
        const IntrebareRaspunsLiber *liberPtr = dynamic_cast<IntrebareRaspunsLiber *>(intrebare);

        while (!corect && vietiRamase > 0) {
            auto timpStart = std::chrono::steady_clock::now();

            afiseazaVieti(vietiRamase, scorGlobal);
            std::cout << "\n" << *intrebare;

            if (liberPtr) {
                ///raspuns liber - citim stringul
                std::string raspunsUtilizatorStr;
                std::cout << "Raspunsul tau (text): ";

                std::getline(std::cin >> std::ws, raspunsUtilizatorStr);
                ///std:ws ignora spatiile albe de la inceput si citim toata linia

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

    ///dupa ce a rasp corect la toate intrebarile
    if (raspunsuriCorecte == intrebari.size()) {
        this->poveste.deblocheaza();
        this->nivelPromovat = true;
        std::cout << "\n FELICITARI! Scorul tau total este: " << scorGlobal << ".\n";
        std::cout << this->poveste;
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

///operator<<
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
