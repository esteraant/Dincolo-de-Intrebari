#ifndef INTREBAREGRILA_H
#define INTREBAREGRILA_H

#include "Intrebare.h"
#include <vector>
#include <memory>

class IntrebareGrila : public Intrebare {
private:
    std::vector<std::string> raspunsuriPosibile;

public:
    ///constructor
    IntrebareGrila(const std::string& t, const std::vector<std::string>& rP, int rC);

    int calculeazaPunctaj() const override;

    ///constructor virtual
    std::unique_ptr<Intrebare> clone() const override;
    void afiseazaDetalii(std::ostream& os) const override;
    virtual bool verificaRaspunsText(const std::string& raspuns_utilizator) const override;
    bool verificaRaspuns(int raspuns_utilizator) const override;
    //size_t getNumarOptiuni() const; ///getter nr de optiuni
    virtual void afiseazaTipIntrebare() const override;
};

#endif
