#ifndef INTREBARERASPUNSLIBER_H
#define INTREBARERASPUNSLIBER_H

/**
 * @brief Derived class for open-ended questions where the user types the answer.
 * This class stores a list of acceptable correct strings and performs
 * text-based validation.
*/

#include "Intrebare.h"
#include <string>
#include <vector>

class IntrebareRaspunsLiber : public Intrebare {
private:
    std::vector<std::string> raspunsuriCorecte;

public:
    IntrebareRaspunsLiber(const std::string &t, const std::vector<std::string> &rC);

    //bool verificaRaspuns(int raspunsUtilizator) const override;
    bool verificaRaspunsText(const std::string &raspunsUtilizator) const override;

    int calculeazaPunctaj() const override;

    std::unique_ptr<Intrebare> clone() const override;

    void afiseazaDetalii(std::ostream &os) const override;

    virtual void afiseazaTipIntrebare() const override;
};

#endif
