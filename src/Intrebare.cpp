#include "../headers/Intrebare.h"

///initializare
size_t Intrebare::nrIntrebariTotale = 0;

///constructor de baza
Intrebare::Intrebare(const std::string &t, int rC) {
    this->text = t;
    this->raspunsCorect = rC;
    Intrebare::nrIntrebariTotale++; ///nr total de obiecte create
}
std::ostream &operator<<(std::ostream &os, const Intrebare &i) {
    i.afiseazaDetalii(os);
    return os;
}

///destructor virtual
/*Intrebare::~Intrebare() {
    Intrebare::nrIntrebariTotale--;
}*/

/*const std::string& Intrebare::getText() const { ///getter pt text
    return text;
}

int Intrebare::getraspunsCorectIndex() const { ///getter pentru raspuns corect
    return raspunsCorect;
}*/
