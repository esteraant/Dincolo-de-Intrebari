#ifndef INTREBARERASPUNSLIBER_H
#define INTREBARERASPUNSLIBER_H

#include "Intrebare.h"
#include <string>
#include <vector>

class IntrebareRaspunsLiber : public Intrebare {
private:
    std::vector<std::string> raspunsuriCorecte;

public:
    IntrebareRaspunsLiber(const std::string& t, const std::vector<std::string>& rC);

    //bool verificaRaspuns(int raspuns_utilizator) const override;
    bool verificaRaspunsText(const std::string& raspuns_utilizator) const override;

    int calculeazaPunctaj() const override;
    std::unique_ptr<Intrebare> clone() const override;
    void afiseazaDetalii(std::ostream& os) const override;
};

#endif
