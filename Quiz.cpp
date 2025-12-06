#include "Quiz.h"
#include <limits>
#include <utility>

///constructor de init
Quiz::Quiz(std::vector<Nivel> niv, const std::string& nume) {
    this->nivele = std::move(niv); ///mutam vectorul de niveluri
    this->numeUtilizator = nume;
}

void Quiz::aplicatie() {
    std::cout << "\nBun venit, " << numeUtilizator << "!\n";
    size_t i = 0;
    int raspuns;
    ///parcurgem toate niv
    while (i < nivele.size()) {
        Nivel& nivel = nivele[i];
        if (!nivel.estePromovat()) {
            nivel.ruleaza_test();
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
