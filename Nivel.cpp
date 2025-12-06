#include "Nivel.h"
#include <utility> // Pentru std::move și std::swap

// Constructor de inițializare
Nivel::Nivel(const std::string& nume, std::vector<std::unique_ptr<Intrebare>> intrebari_, const CapitolPoveste& poveste_)
    : nivelPromovat{false}
{
    this->numeNivel = nume;
    this->intrebari = std::move(intrebari_);
    this->poveste = poveste_;
}

// Constructor de copiere (Deep Copy)
Nivel::Nivel(const Nivel& nivel)
    : numeNivel{nivel.numeNivel}, poveste{nivel.poveste}, nivelPromovat{nivel.nivelPromovat}
{
    std::cout << "Nivel " << nivel.numeNivel << " copiat (Deep Clone).\n";

    // Copierea profunda a vectorului de intrebari folosind clone() (Constructor Virtual)
    for (const auto& intrebare_ptr : nivel.intrebari) {
        this->intrebari.push_back(intrebare_ptr->clone());
    }
}

// Operator de atribuire (Deep Copy - Copy-and-Swap Idiom)
Nivel& Nivel::operator=(const Nivel& nivel) {
    std::cout << "Atribuire Nivel " << nivel.numeNivel << " (Deep Clone).\n";

    if (this != &nivel) {
        // Creează o copie temporară
        Nivel temp = nivel;

        // Schimbăm resursele
        std::swap(numeNivel, temp.numeNivel);
        std::swap(intrebari, temp.intrebari);
        std::swap(poveste, temp.poveste);
        std::swap(nivelPromovat, temp.nivelPromovat);
    }
    return *this;
}

// rularea testului
void Nivel::ruleaza_test() {
    int raspuns_utilizator;
    size_t scor_total = 0; // Pentru a folosi functia virtuala specifica temei
    size_t raspunsuri_corecte = 0;

    std::cout << "\n " << numeNivel << " \n";
    std::cout << "Raspunde corect la fiecare intrebare pentru a continua!\n";

    for (size_t i = 0; i < intrebari.size(); i++) {
        Intrebare* intrebare = intrebari[i].get();
        bool corect = false;

        // Identificăm tipul de întrebare: Răspuns Liber?
        IntrebareRaspunsLiber* liber_ptr = dynamic_cast<IntrebareRaspunsLiber*>(intrebare);

        while (!corect) {
            std::cout << "\n" << *intrebare;

            if (liber_ptr) {
                // CAZUL 1: RASPUNS LIBER (Citim string)
                std::string raspuns_utilizator_str;
                std::cout << "Raspunsul tau (text): ";

                // std::ws ignoră spațiile albe de la început, și apoi citim intreaga linie
                std::getline(std::cin >> std::ws, raspuns_utilizator_str);

                if (intrebare->verificaRaspunsText(raspuns_utilizator_str)) { // Apel polimorfic nou
                    std::cout << "Raspuns CORECT! Ai castigat " << intrebare->calculeazaPunctaj() << " puncte.\n";
                    scor_total += intrebare->calculeazaPunctaj();
                    raspunsuri_corecte++;
                    corect = true;
                } else {
                    std::cout << "\n Raspuns GRESIT! \n";
                    std::cout << "Incearca din nou.\n";
                }

            } else {
                // CAZUL 2: RASPUNS PE INDICE (Citim int)
                int raspuns_utilizator_int;
                std::cout << "Raspunsul tau (nr optiune): ";

                if (!(std::cin >> raspuns_utilizator_int)) {
                    // Gestiune erori citire
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nIntrare invalida. Te rog introdu numarul optiunii.\n";
                    continue;
                }

                if (intrebare->verificaRaspuns(raspuns_utilizator_int)) { // Apel polimorfic existent
                    std::cout << "Raspuns CORECT! Ai castigat " << intrebare->calculeazaPunctaj() << " puncte.\n";
                    scor_total += intrebare->calculeazaPunctaj();
                    raspunsuri_corecte++;
                    corect = true;
                } else {
                    std::cout << "\n Raspuns GRESIT! \n";
                    std::cout << "Incearca din nou.\n";
                }
                // Dupa citirea int, curatam buffer-ul
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    // Dupa ce a raspuns corect la toate intrebarile
    if (raspunsuri_corecte == intrebari.size()) {
        this->poveste.deblocheaza();
        this->nivelPromovat = true;
        std::cout << "\n FELICITARI! Capitol deblocat! Scorul tau total pentru acest nivel este: " << scor_total << ".\n";
        std::cout << this->poveste;
    }
}


// Getter pt numeNivel
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


// Operator<<
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
