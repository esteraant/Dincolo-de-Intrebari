#ifndef INTREBAREAADEVARATFALS_H
#define INTREBAREAADEVARATFALS_H
/**
 * @brief Derived class for True/False style questions.
 * This class handles binary choice questions where the correct answer
 * is represented as 0 (False) or 1 (True).
 */

#include "Intrebare.h"
#include <memory>

///0 - Fals; 1 - Adevarat
class IntrebareAdevaratFals : public Intrebare {
public:
    IntrebareAdevaratFals(const std::string &t, int rC);

    bool verificaRaspuns(int raspunsUtilizator) const override;

    virtual bool verificaRaspunsText(const std::string &raspunsUtilizator) const override;

    int calculeazaPunctaj() const override;

    std::unique_ptr<Intrebare> clone() const override;

    void afiseazaDetalii(std::ostream &os) const override;

    virtual void afiseazaTipIntrebare() const override;
};

#endif
