#ifndef INTREBAREAADEVARATFALS_H
#define INTREBAREAADEVARATFALS_H

#include "Intrebare.h"
#include <memory>

///0 - Fals; 1 - Adevarat
class IntrebareAdevaratFals : public Intrebare {
public:
    IntrebareAdevaratFals(const std::string& t, int rC);
    bool verificaRaspuns(int raspuns_utilizator) const override;
    virtual bool verificaRaspunsText(const std::string& raspuns_utilizator) const override;
    int calculeazaPunctaj() const override;

    std::unique_ptr<Intrebare> clone() const override;
    void afiseazaDetalii(std::ostream& os) const override;
};

#endif
