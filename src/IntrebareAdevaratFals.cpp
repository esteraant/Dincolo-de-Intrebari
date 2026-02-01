#include "../headers/IntrebareAdevaratFals.h"
#include <memory>

///apelarea constructorului clasei de baza
IntrebareAdevaratFals::IntrebareAdevaratFals(const std::string &t, int rC)
    : Intrebare(t, rC) {
}

///utilizatorul introduce 1 - A; 2 - F
bool IntrebareAdevaratFals::verificaRaspuns(int raspunsUtilizator) const {
    int val;
    if (raspunsUtilizator == 1) val = 1;
    else val = 0;
    return val == raspunsCorect;
}

bool IntrebareAdevaratFals::verificaRaspunsText(const std::string &raspunsUtilizator) const {
    static_cast<void>(raspunsUtilizator);
    return false; ///intrebarea nu accepta raspunsuri de tip text
}

int IntrebareAdevaratFals::calculeazaPunctaj() const {
    return 1;
}

void IntrebareAdevaratFals::afiseazaTipIntrebare() const {
    std::cout << "Tip: Raspuns Adevarat/Fals.\n";
}

///constructor virtual (Clone)
std::unique_ptr<Intrebare> IntrebareAdevaratFals::clone() const {
    return std::make_unique<IntrebareAdevaratFals>(*this);
}

void IntrebareAdevaratFals::afiseazaDetalii(std::ostream &os) const {
    os << "  1) Adevarat\n" << "  2) Fals\n";
}
