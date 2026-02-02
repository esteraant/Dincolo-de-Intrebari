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

void StatisticiJoc::afiseazaStatistici(int totalNivele) const {
    std::cout << "\n STATISTICI FINALE \n";
    std::cout << "Nivele finalizate: " << getProcentProgres(totalNivele) << "%\n";

    float procentPoveste = (totalNivele > 0) ? (static_cast<float>(nrPovestiDescoperite) / totalNivele) * 100 : 0;
    std::cout << "Poveste descoperita: " << procentPoveste << "%\n";
    std::cout << "Acuratete raspunsuri: " << calculeazaAcuratetea() << "%\n";
}
