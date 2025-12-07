#include "Quiz.h"
#include <limits>
#include <utility>

///constructor de init
Quiz::Quiz(const std::string& nume, std::vector<Nivel> niv)
        : numeUtilizator{nume}, nivele{std::move(niv)}, scorTotalGlobal{0}
{
    //this->nivele = std::move(niv); ///mutam vectorul de niveluri
    //this->numeUtilizator = nume;
}

void Quiz::aplicatie() {
    std::cout << "\nBun venit, " << numeUtilizator << "!\n";
    size_t i = 0;
    int raspuns;
    ///parcurgem toate niv
    while (i < nivele.size()) {
        Nivel& nivel = nivele[i];
        if (!nivel.estePromovat()) {
            if (!nivel.ruleaza_test(scorTotalGlobal)) {
                ///daca ruleaza_test returneaza false - nu a fost promovat din cauza vietilor
                std::cout << "\nAplicatia se opreste. Ai ramas fara vieti in timpul jocului.\n";
                return;
            }
        }

        if (i == nivele.size() - 1) {
            std::cout << "\n FELICITARI!! Ai deblocat toate capitolele!! \n";
            break;
        }

        std::cout << "\n\n";
        std::cout << "Vrei sa continui la Nivelul " << i + 2 << "? (1/0): ";

        if (!(std::cin >> raspuns)) {
            std::cin.clear(); ///daca utilizatorul scrie ceva gresit (string in loc de int)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            raspuns = 0;
        }

        if (raspuns == 1) {
            i++; ///trecem la niv urm
        }
        else {
            std::cout << "\nAplicatia se opreste. Sper ca ai avut o experienta placuta!\n";
            return;
        }
    }
}

///operator<<
std::ostream& operator<<(std::ostream& os, const Quiz& qa) {
    os << "\nSituatii finale pentru " << qa.numeUtilizator << ":\n";
    for (const Nivel& nivel : qa.nivele) {
        os << nivel;
    }
    return os;
}
