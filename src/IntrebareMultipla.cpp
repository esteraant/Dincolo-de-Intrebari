#include "../headers/IntrebareMultipla.h"
#include <sstream>

IntrebareMultipla::IntrebareMultipla(const std::string &t,
                                     const std::vector<std::string> &rP,
                                     const std::set<int> &indiciCorecti)
    : Intrebare(t, -1) {
    this->raspunsuriPosibile = rP;
    this->indiciRaspunsuriCorecte = indiciCorecti;
}

///verificam daca raspunsul introdus face parte din setul corect
bool IntrebareMultipla::verificaRaspuns(int raspunsUtilizator) const {
    return indiciRaspunsuriCorecte.count(raspunsUtilizator);
}

bool IntrebareMultipla::verificaRaspunsText(const std::string &raspunsUtilizator) const {
    static_cast<void>(raspunsUtilizator);
    return false;
}


int IntrebareMultipla::calculeazaPunctaj() const {
    return 4;
}

///constructor virutal
std::unique_ptr<Intrebare> IntrebareMultipla::clone() const {
    return std::make_unique<IntrebareMultipla>(*this);
}

void IntrebareMultipla::afiseazaDetalii(std::ostream &os) const {
    for (size_t i = 0; i < raspunsuriPosibile.size(); i++) {
        os << "  " << i + 1 << ") " << raspunsuriPosibile[i] << "\n";
    }
    os << "  (ATENTIE! Exista mai multe variante corecte!)\n";
}

void IntrebareMultipla::afiseazaTipIntrebare() const {
    std::cout << "Tip: Raspunsuri Multiple.\n";
}

/*size_t IntrebareMultipla::getNumarOptiuni() const {
    return raspunsuriPosibile.size();
}
*/
