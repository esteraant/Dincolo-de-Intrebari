#include "../headers/StatisticiJoc.h"
#include <iostream>

void StatisticiJoc::adaugaRaspuns(bool corect) {
    raspunsuriTotale++;
    if (corect) {
        raspunsuriCorecte++;
    }
}

double StatisticiJoc::calculeazaAcuratetea() const {
    if (raspunsuriTotale == 0) {
        return 0.0;
    }
    ///calculam procentul
    return static_cast<double>(raspunsuriCorecte) / raspunsuriTotale * 100.0;
}

void StatisticiJoc::afiseazaStatistici() const {
    std::cout << "\n STATISTICI FINALE \n";
    std::cout << "Raspunsuri totale: " << raspunsuriTotale << "\n";
    std::cout << "Raspunsuri corecte: " << raspunsuriCorecte << "\n";
    std::cout << "ACURATETE GLOBALA: " << calculeazaAcuratetea() << "%\n\n";
}
