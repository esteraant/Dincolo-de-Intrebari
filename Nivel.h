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

class Nivel {
private:
    std::string numeNivel;
    std::vector<std::unique_ptr<Intrebare>> intrebari;
    CapitolPoveste poveste;
    bool nivelPromovat;

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
    Nivel(Nivel&& nivel) = default;
    Nivel& operator=(Nivel&& nivel) = default;

    ///destructor
    ~Nivel() = default;

    void ruleaza_test();

    ///getter pt numeNivel
    const std::string& getNumeNivel() const;

    bool estePromovat() const;

    ///getter pentru a accesa un obiect Intrebare
    Intrebare* getIntrebare(size_t index) const;

    ///getter pentru a accesa capitolul
    CapitolPoveste* getCapitol() const;

    ///operator<<
    friend std::ostream& operator<<(std::ostream& os, const Nivel& niv);
};

#endif
