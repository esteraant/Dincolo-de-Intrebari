#ifndef STATISTICIJOC_H
#define STATISTICIJOC_H

/**
 * @brief Tracks and calculates player performance metrics during a quiz session.
 * This class maintains counters for total questions answered and correct answers,
 * providing methods to calculate accuracy percentages and display summaries.
 */
#include <cstddef>

class StatisticiJoc {
private:
    size_t raspunsuriTotale = 0;
    size_t raspunsuriCorecte = 0;
    size_t nrNiveleTerminate = 0;
    size_t nrPovestiDescoperite = 0;

public:
    StatisticiJoc() = default;

    void bifeazaNivelTerminat() { nrNiveleTerminate++; }
    void bifeazaPovesteDescoperita() { nrPovestiDescoperite++; }
    void adaugaRaspuns(bool corect);

    ///calculam procentul
    [[nodiscard]]double calculeazaAcuratetea() const;

    void afiseazaStatistici(int totalNivele) const;
    [[nodiscard]]float getProcentProgres(int totalNivele) const {
        if (totalNivele == 0) return 0;
        return (static_cast<float>(nrNiveleTerminate) / totalNivele) * 100;
    }
};

#endif
