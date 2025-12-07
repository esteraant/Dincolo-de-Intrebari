#ifndef NIVEL_H
#define NIVEL_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>
#include "Intrebare.h"
#include "CapitolPoveste.h"
#include "IntrebareRaspunsLiber.h"
#include "StatisticiJoc.h"

class Nivel {
private:
    std::string numeNivel;
    std::vector<std::unique_ptr<Intrebare>> intrebari;
    CapitolPoveste poveste;
    bool nivelPromovat;
    void afiseaza_vieti(int count, size_t scor) const;

public:
    ///contructor de initializare
    Nivel(const std::string& nume, std::vector<std::unique_ptr<Intrebare>> intrebari_, const CapitolPoveste& poveste_);

    ///constructor  default
    Nivel() : nivelPromovat{false} {}

    ///constructor de copiere
    Nivel(const Nivel& nivel);

    ///op de atribuire
    Nivel& operator=(const Nivel& nivel);

    ///operator de mutare - transfera proprietatea vectorului de intrebari
    //Nivel(Nivel&& nivel) = default;
    //Nivel& operator=(Nivel&& nivel) = default;

    ///destructor
    ~Nivel() = default;

    bool ruleaza_test(size_t& scorGlobal, StatisticiJoc& stats);

    ///getter pt numeNivel
    const std::string& getNumeNivel() const;

    bool estePromovat() const;

    const Intrebare& getIntrebare(size_t i) const;
    const CapitolPoveste& getCapitol() const;

    ///operator<<
    friend std::ostream& operator<<(std::ostream& os, const Nivel& niv);
};

#endif
