#ifndef INTREBAREGRILA_H
#define INTREBAREGRILA_H

/**
 * @brief Derived class for multiple-choice questions with a single correct answer.
 * This class stores a list of possible answers and validates the user's choice
 * based on the index of the selected option.
 */
#include "Intrebare.h"
#include <vector>
#include <memory>

class IntrebareGrila : public Intrebare {
private:
    std::vector<std::string> raspunsuriPosibile;

public:
    ///constructor
    IntrebareGrila(const std::string &t, const std::vector<std::string> &rP, int rC);

    [[nodiscard]]int calculeazaPunctaj() const override;

    ///constructor virtual
    [[nodiscard]]std::unique_ptr<Intrebare> clone() const override;

    void afiseazaDetalii(std::ostream &os) const override;

    [[nodiscard]]virtual bool verificaRaspunsText(const std::string &raspunsUtilizator) const override;

    [[nodiscard]]bool verificaRaspuns(int raspunsUtilizator) const override;

    [[nodiscard]]size_t getNumarOptiuni() const { return raspunsuriPosibile.size(); }
     ///getter nr de optiuni
    virtual void afiseazaTipIntrebare() const override;

};

#endif
