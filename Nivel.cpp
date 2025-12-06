#include "Nivel.h"
#include <utility>

///constructor de initializare
Nivel::Nivel(const std::string& nume, std::vector<std::unique_ptr<Intrebare>> intrebari_, const CapitolPoveste& poveste_)
    : nivelPromovat{false}
{
    this->numeNivel = nume;
    this->intrebari = std::move(intrebari_);
    this->poveste = poveste_;
}

///constructor de copiere
Nivel::Nivel(const Nivel& nivel)
    : numeNivel{nivel.numeNivel}, poveste{nivel.poveste}, nivelPromovat{nivel.nivelPromovat}
{
    ///std::cout << "Nivel " << nivel.numeNivel << " copiat.\n";
    for (const std::unique_ptr<Intrebare>& intrebare_ptr : nivel.intrebari) {
    this->intrebari.push_back(intrebare_ptr->clone());
}
}

///operator de atribuire
Nivel& Nivel::operator=(const Nivel& nivel) {
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

void Nivel::ruleaza_test() {
    int raspuns_utilizator;
    size_t scor_total = 0;
    size_t raspunsuri_corecte = 0;

    std::cout << "\n " << numeNivel << " \n";
    std::cout << "Raspunde corect la fiecare intrebare pentru a continua!\n";

    for (size_t i = 0; i < intrebari.size(); i++) {
        Intrebare* intrebare = intrebari[i].get();
        bool corect = false;

        ///idenfiticam tipul de intrebare - daca e raspuns liber
        IntrebareRaspunsLiber* liber_ptr = dynamic_cast<IntrebareRaspunsLiber*>(intrebare);

        while (!corect) {
            std::cout << "\n" << *intrebare;

            if (liber_ptr) {
                ///raspuns liber - citim stringul
                std::string raspuns_utilizator_str;
                std::cout << "Raspunsul tau (text): ";

                std::getline(std::cin >> std::ws, raspuns_utilizator_str);
                ///std:ws ignora spatiile albe de la inceput si citim toata linia

                if (intrebare->verificaRaspunsText(raspuns_utilizator_str)) {
                    std::cout << "Raspuns CORECT! Ai castigat " << intrebare->calculeazaPunctaj() << " puncte.\n";
                    scor_total += intrebare->calculeazaPunctaj();
                    raspunsuri_corecte++;
                    corect = true;
                } else {
                    std::cout << "\n Raspuns GRESIT! \n";
                    std::cout << "Incearca din nou.\n";
                }

            } else {
                ///altfel citim int
                int raspuns_utilizator_int;
                std::cout << "Raspunsul tau (nr optiune): ";

                if (!(std::cin >> raspuns_utilizator_int)) { ///erori
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nIntrare invalida. Te rog introdu numarul optiunii.\n";
                    continue;
                }

                if (intrebare->verificaRaspuns(raspuns_utilizator_int)) {
                    std::cout << "Raspuns CORECT! Ai castigat " << intrebare->calculeazaPunctaj() << " puncte.\n";
                    scor_total += intrebare->calculeazaPunctaj();
                    raspunsuri_corecte++;
                    corect = true;
                } else {
                    std::cout << "\n Raspuns GRESIT! \n";
                    std::cout << "Incearca din nou.\n";
                }
                ///curatam buffer-ul
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    ///dupa ce a rasp corect la toate intrebarile
    if (raspunsuri_corecte == intrebari.size()) {
        this->poveste.deblocheaza();
        this->nivelPromovat = true;
        std::cout << "\n FELICITARI! Capitol deblocat! Scorul tau total pentru acest nivel este: " << scor_total << ".\n";
        std::cout << this->poveste;
    }
}


///getter pt numeNivel
const std::string& Nivel::getNumeNivel() const {
    return numeNivel;
}

bool Nivel::estePromovat() const {
    return nivelPromovat;
}

Intrebare* Nivel::getIntrebare(size_t index) const {
    if (index < intrebari.size()) {
        return intrebari[index].get();
    }
    return nullptr;
}

CapitolPoveste* Nivel::getCapitol() const {
    return (CapitolPoveste*)&poveste;
}


///operator<<
std::ostream& operator<<(std::ostream& os, const Nivel& niv) {
    os << "\n=== Nivel " << niv.numeNivel << " ===\n";
    os << "Status: ";
    if (niv.nivelPromovat) os << "PROMOVAT";
    else os << "NEPROMOVAT";
    os << "\n";
    os << "Intrebari: " << niv.intrebari.size() << "\n";
    os << niv.poveste;
    return os;
}
