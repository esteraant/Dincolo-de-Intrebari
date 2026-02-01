#ifndef GENERATOR_H
#define GENERATOR_H

/**
 * @brief Factory class responsible for creating different types of Question objects.
 * This class implements the Factory Method design pattern.
 *
*/
#include "Intrebare.h"
#include "IntrebareGrila.h"
#include "IntrebareAdevaratFals.h"
#include "IntrebareRaspunsLiber.h"
#include "IntrebareMultipla.h"
#include <memory>
#include <vector>
#include <string>
#include <set>

class Generator {
public:
    //metoda Factory - design pattern
    static std::unique_ptr<Intrebare> creeaza(
        char tip,
        const std::string &text,
        const std::vector<std::string> &optiuni,
        int raspunsUnic,
        const std::set<int> &indiciMultipli,
        const std::vector<std::string> &raspunsuriLibere) {
        if (tip == 'G') return std::make_unique<IntrebareGrila>(text, optiuni, raspunsUnic - 1);
        if (tip == 'A') return std::make_unique<IntrebareAdevaratFals>(text, raspunsUnic == 1 ? 1 : 0);
        if (tip == 'L') return std::make_unique<IntrebareRaspunsLiber>(text, raspunsuriLibere);
        if (tip == 'M') return std::make_unique<IntrebareMultipla>(text, optiuni, indiciMultipli);

        return nullptr;
    }
};

#endif
