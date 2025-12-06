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
    ///constructor de init
    Quiz(std::vector<Nivel> niv, const std::string& nume);

    ///dezactivarea copierii pt a evita erori la Nivel
    Quiz(const Quiz& qa) = delete;
    Quiz& operator=(const Quiz& qa) = delete;

    ///permiterea mutarii
    Quiz(Quiz&& qa) = default;
    Quiz& operator=(Quiz&& qa) = default;

    void aplicatie();

    friend std::ostream& operator<<(std::ostream& os, const Quiz& qa);
};

#endif
