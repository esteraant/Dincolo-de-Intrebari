#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <vector>
#include <string>
#include "Nivel.h"

class Quiz {
private:
    std::vector<Nivel> nivele;
    std::string numeUtilizator;

public:
    const std::vector<Nivel>& get_nivele() const {
        return nivele;
    }
    // Constructor de inițializare
    Quiz(std::vector<Nivel> niv, const std::string& nume);

    // Dezactivăm copierea (pentru a evita erori din cauza Nivelului non-copiabil)
    Quiz(const Quiz& qa) = delete;
    Quiz& operator=(const Quiz& qa) = delete;

    // Permitem mutarea
    Quiz(Quiz&& qa) = default;
    Quiz& operator=(Quiz&& qa) = default;

    void aplicatie();

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Quiz& qa);
};

#endif // QUIZ_H
