#ifndef INTREBAREMULTIPLA_H
#define INTREBAREMULTIPLA_H

/**
 * @brief Derived class for questions that require multiple correct answers to be selected.
 * This class stores a set of correct indices and validates user input by checking
 * if the provided index is part of the correct answers set.
 */

#include "Intrebare.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

class IntrebareMultipla : public Intrebare {
private:
    std::vector<std::string> raspunsuriPosibile;
    std::set<int> indiciRaspunsuriCorecte;

public:
    ///constructor
    IntrebareMultipla(const std::string &t,
                      const std::vector<std::string> &rP,
                      const std::set<int> &indiciCorecti);

    bool verificaRaspuns(int raspunsUtilizator) const override;

    virtual bool verificaRaspunsText(const std::string &raspunsUtilizator) const override;

    int calculeazaPunctaj() const override;

    std::unique_ptr<Intrebare> clone() const override;

    void afiseazaDetalii(std::ostream &os) const override;

    virtual void afiseazaTipIntrebare() const override;

    //size_t getNumarOptiuni() const;
};

#endif
