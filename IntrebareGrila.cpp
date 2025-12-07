#include "IntrebareGrila.h"

///constructor - apeleaza constructorul clasei de baza
IntrebareGrila::IntrebareGrila(const std::string& t, const std::vector<std::string>& rP, int rC)
    : Intrebare(t, rC) {
    this->raspunsuriPosibile = rP;
}

bool IntrebareGrila::verificaRaspuns(int raspuns_utilizator) const {
    return (raspuns_utilizator - 1) == raspunsCorect;
}

int IntrebareGrila::calculeazaPunctaj() const {
    return 2; /// +2 puncte
}
bool IntrebareGrila::verificaRaspunsText(const std::string& raspuns_utilizator) const {
    static_cast<void>(raspuns_utilizator);
    return false;
}


///constructor virtual
std::unique_ptr<Intrebare> IntrebareGrila::clone() const {
    return std::make_unique<IntrebareGrila>(*this);
}


void IntrebareGrila::afiseazaDetalii(std::ostream& os) const {
    for (size_t i = 0; i < raspunsuriPosibile.size(); i++) {
        os << "  " << i + 1 << ") " << raspunsuriPosibile[i] << "\n";
    }
    os << "\n";
}

size_t IntrebareGrila::getNumarOptiuni() const { ///getter nr de optiuni
    return raspunsuriPosibile.size();
}

