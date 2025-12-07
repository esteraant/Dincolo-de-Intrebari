#include "IntrebareAdevaratFals.h"
#include <memory>

///apelarea constructorului clasei de baza
IntrebareAdevaratFals::IntrebareAdevaratFals(const std::string& t, int rC)
    : Intrebare(t, rC) {}

///utilizatorul introduce 1 - A; 2 - F
bool IntrebareAdevaratFals::verificaRaspuns(int raspuns_utilizator) const {
    int val;
    if(raspuns_utilizator == 1) val = 1;
    else val = 0;
    return val == raspunsCorect;
}

bool IntrebareAdevaratFals::verificaRaspunsText(const std::string& raspuns_utilizator) const {
    return false; ///intrebarea nu accepta raspunsuri de tip text
}

int IntrebareAdevaratFals::calculeazaPunctaj() const {
    return 1;
}
\
///constructor virtual (Clone)
std::unique_ptr<Intrebare> IntrebareAdevaratFals::clone() const {
    return std::unique_ptr<Intrebare>(new IntrebareAdevaratFals(*this));
}

void IntrebareAdevaratFals::afiseazaDetalii(std::ostream& os) const {
    os << "  1) Adevarat\n"<< "  2) Fals\n";
}
