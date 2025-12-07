#ifndef STATISTICIJOC_H
#define STATISTICIJOC_H

#include <cstddef>

class StatisticiJoc {
private:
    size_t raspunsuriTotale = 0;
    size_t raspunsuriCorecte = 0;

public:
    StatisticiJoc() = default;
    ///metoda pt actualizarea starii
    void adaugaRaspuns(bool corect);
    ///calculam procentul
    double calculeazaAcuratetea() const;
    ///afisarea datelor
    void afiseazaStatistici() const;
};

#endif
