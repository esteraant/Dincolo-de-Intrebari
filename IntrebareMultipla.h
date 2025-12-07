#ifndef INTREBAREMULTIPLA_H
#define INTREBAREMULTIPLA_H

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
    IntrebareMultipla(const std::string& t,
                     const std::vector<std::string>& rP,
                     const std::set<int>& indiciCorecti);

    bool verificaRaspuns(int raspuns_utilizator) const override;
    virtual bool verificaRaspunsText(const std::string& raspuns_utilizator) const override;
    int calculeazaPunctaj() const override;

    std::unique_ptr<Intrebare> clone() const override;
    void afiseazaDetalii(std::ostream& os) const override;

    //size_t getNumarOptiuni() const;
};

#endif
