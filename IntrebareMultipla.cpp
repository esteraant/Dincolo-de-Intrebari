#include "IntrebareMultipla.h"
#include <sstream>

///constructor
IntrebareMultipla::IntrebareMultipla(const std::string& t,
                                     const std::vector<std::string>& rP,
                                     const std::set<int>& indiciCorecti)
    : Intrebare(t, -1)
{
    this->raspunsuriPosibile = rP;
    this->indiciRaspunsuriCorecte = indiciCorecti;
}

///verificam daca raspunsul introdus face parte din setul corect
bool IntrebareMultipla::verificaRaspuns(int raspuns_utilizator) const  {
    return indiciRaspunsuriCorecte.count(raspuns_utilizator);
}

bool IntrebareMultipla::verificaRaspunsText(const std::string& raspuns_utilizator) const  {
    return false;
}


int IntrebareMultipla::calculeazaPunctaj() const {
    return 4;
}

///constructor virutal
std::unique_ptr<Intrebare> IntrebareMultipla::clone() const {
    return std::unique_ptr<Intrebare>(new IntrebareMultipla(*this));
}

void IntrebareMultipla::afiseazaDetalii(std::ostream& os) const {
    for (size_t i = 0; i < raspunsuriPosibile.size(); i++) {
        os << "  " << i + 1 << ") " << raspunsuriPosibile[i] << "\n";
    }
    os << "  (ATENTIE! Exista mai multe variante corecte!)\n";
}

size_t IntrebareMultipla::getNumarOptiuni() const {
    return raspunsuriPosibile.size();
}
