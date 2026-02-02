#ifndef QUIZ_H
#define QUIZ_H

/**
 * @brief The main controller class that orchestrates the entire gameplay experience.
 * This class manages the sequence of levels, tracks the global score,
 * and aggregates game statistics. It acts as the central engine of the application.
 */

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "Nivel.h"
#include "StatisticiJoc.h"

class Quiz {
private:
    std::string numeUtilizator;
    std::vector<Nivel> nivele;
    size_t scorTotalGlobal = 0;
    StatisticiJoc statistici;

public:
    // const std::vector<Nivel> &get_nivele() const {
    //     return nivele;
    // }

    [[nodiscard]]size_t getScorTotal() const { return scorTotalGlobal; }

    Quiz(const std::string &nume, std::vector<Nivel> nivele_);

    ///dezactivarea copierii pt a evita erori la Nivel
    Quiz(const Quiz &qa) = delete;

    Quiz &operator=(const Quiz &qa) = delete;

    ///permiterea mutarii
    Quiz(Quiz &&qa);

    Quiz &operator=(Quiz &&qa);

    void aplicatie();

    friend std::ostream &operator<<(std::ostream &os, const Quiz &qa);
    void oferaAjutor(const Intrebare* i) const;
    [[nodiscard]]const StatisticiJoc& getStatistici() const { return statistici; }
};

#endif
