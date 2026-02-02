#include "../headers/Quiz.h"
#include <limits>
#include <utility>
#include "IntrebareGrila.h"
#include "IntrebareAdevaratFals.h"
#include "IntrebareRaspunsLiber.h"
Quiz::Quiz(const std::string &nume, std::vector<Nivel> niv)
    : numeUtilizator{nume},
      nivele{std::move(niv)},
      scorTotalGlobal{0},
      statistici{} {
}

Quiz::Quiz(Quiz &&qa)
    : numeUtilizator{std::move(qa.numeUtilizator)},
      nivele{std::move(qa.nivele)},
      scorTotalGlobal{qa.scorTotalGlobal},
      statistici{std::move(qa.statistici)} {
    qa.scorTotalGlobal = 0;
}

Quiz &Quiz::operator=(Quiz &&qa) {
    if (this != &qa) {
        //muta membrii mari
        numeUtilizator = std::move(qa.numeUtilizator);
        nivele = std::move(qa.nivele);
        statistici = std::move(qa.statistici);

        //copiaza membrii mici
        scorTotalGlobal = qa.scorTotalGlobal;
        qa.scorTotalGlobal = 0;
    }
    return *this;
}
void Quiz::oferaAjutor(const Intrebare* i) const {
    if (!i) return;

    std::cout << "\n[HINT]: ";

    if (auto* grila = dynamic_cast<const IntrebareGrila*>(i)) {
        std::cout << "Aceasta este o intrebare cu " << grila->getNumarOptiuni()
                  << " variante de raspuns. Doar una este corecta!";
    }
    else if (dynamic_cast<const IntrebareAdevaratFals*>(i)) {
        std::cout << "Ai 50% sanse! Analizeaza bine afirmatia.";
    }
    else if (dynamic_cast<const IntrebareRaspunsLiber*>(i)) {
        std::cout << "Atentie la ortografie! Raspunsul trebuie sa fie exact.";
    }
    else {
        std::cout << "Citeste cu atentie cerinta.";
    }
    std::cout << std::endl;
}

void Quiz::aplicatie() {
    std::cout << "\nBun venit, " << numeUtilizator << "!\n";
    size_t i = 0;
    int raspuns;
    ///parcurgem toate niv
    while (i < nivele.size()) {
        Nivel &nivel = nivele[i];
        if (nivel.getNrIntrebari() > 0) {
            oferaAjutor(nivel.getIntrebare(0));
        }
        if (!nivel.estePromovat()) {
            if (!nivel.ruleazaTest(scorTotalGlobal, statistici)) {
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
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            raspuns = 0;
        }

        if (raspuns == 1) {
            i++;
            statistici.afiseazaStatistici(static_cast<int>(nivele.size()));
        } else {
            std::cout << "\nAplicatia se opreste. Sper ca ai avut o experienta placuta!\n";
            return;
        }
    }

    ///statistici finale
    std::cout << "\n\nDoresti sa vezi statisticile globale de performanta? (1 - Da / 0 - Nu): ";
    if (!(std::cin >> raspuns)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        raspuns = 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (raspuns == 1) {
        statistici.afiseazaStatistici(static_cast<int>(nivele.size()));
    } else {
        std::cout << "Statisticile nu vor fi afisate. Multumiri!\n";
    }
}

std::ostream &operator<<(std::ostream &os, const Quiz &qa) {
    os << "\nSituatii finale pentru " << qa.numeUtilizator << ":\n";
    for (const Nivel &nivel: qa.nivele) {
        os << nivel;
    }
    return os;
}
