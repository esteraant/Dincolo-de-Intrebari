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
    // Constructor de inițializare
    Nivel(const std::string& nume, std::vector<std::unique_ptr<Intrebare>> intrebari_, const CapitolPoveste& poveste_);

    // Constructor default
    Nivel() : nivelPromovat{false} {}

    // Constructor de copiere personalizat (pentru Deep Copy, folosind clone)
    Nivel(const Nivel& nivel);

    // Operator de atribuire personalizat (pentru Deep Copy)
    Nivel& operator=(const Nivel& nivel);

    // Operator de mutare (default, deoarece unique_ptr poate fi mutat)
    Nivel(Nivel&& nivel) = default;
    Nivel& operator=(Nivel&& nivel) = default;

    // Destructor (default)
    ~Nivel() = default;

    // Rularea testului
    void ruleaza_test();

    // Getter pt numeNivel
    const std::string& getNumeNivel() const;

    bool estePromovat() const;

    // Getter pentru a accesa un obiect Intrebare (polimorfic)
    Intrebare* getIntrebare(size_t index) const;

    // Getter pentru a accesa Capitolul
    CapitolPoveste* getCapitol() const;

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Nivel& niv);
};

#endif // NIVEL_H
