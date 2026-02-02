#ifndef NIVEL_H
#define NIVEL_H

/**
 * @brief Manages a game level, including its set of questions and the associated story chapter.
 * This class handles the gameplay loop for a specific level, tracks player lives,
 * and determines if the level's story chapter should be unlocked.
 */

#include <iostream>
#include <vector>
#include <string>
//#include <limits>
#include <memory>
#include "Intrebare.h"
#include "CapitolPoveste.h"
//#include "IntrebareRaspunsLiber.h"
#include "StatisticiJoc.h"

class Nivel {
private:
    std::string numeNivel;
    std::vector<std::unique_ptr<Intrebare> > intrebari;
    CapitolPoveste poveste;
    bool nivelPromovat;

    // void afiseazaVieti(int count, size_t scor) const;

public:
    Nivel(const std::string &nume, std::vector<std::unique_ptr<Intrebare> > intrebari_, const CapitolPoveste &poveste_);
    Nivel() : nivelPromovat{false} {}
    Nivel(const Nivel &nivel);

    Nivel &operator=(const Nivel &nivel);

    ///operator de mutare - transfera proprietatea vectorului de intrebari
    //Nivel(Nivel&& nivel) = default;
    //Nivel& operator=(Nivel&& nivel) = default;

    ~Nivel() = default;

    bool ruleazaTest(size_t &scorGlobal, StatisticiJoc &stats);

    [[nodiscard]]size_t getNrIntrebari() const { return intrebari.size(); }
    [[nodiscard]]const Intrebare* getIntrebare(size_t index) const { return intrebari.at(index).get(); }
    ///getter pt numeNivel
    //const std::string& getNumeNivel() const;


    [[nodiscard]]bool estePromovat() const;

    //const Intrebare& getIntrebare(size_t i) const;
    //const CapitolPoveste& getCapitol() const;
    [[nodiscard]]bool esteFinalizat() const { return nivelPromovat; }

    ///operator<<
    friend std::ostream &operator<<(std::ostream &os, const Nivel &niv);
};

#endif
