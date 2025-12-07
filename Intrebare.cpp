#include "Intrebare.h"

///initializare
size_t Intrebare::nr_intrebari_totale = 0;

///constructor de baza
Intrebare::Intrebare(const std::string& t, int rC)
{
    this->text = t;
    this->raspunsCorect = rC;
    Intrebare::nr_intrebari_totale++;  ///nr total de obiecte create
}

///destructor virtual
/*Intrebare::~Intrebare() {
    Intrebare::nr_intrebari_totale--;
}*/

const std::string& Intrebare::getText() const { ///getter pt text
    return text;
}

int Intrebare::getraspunsCorectIndex() const { ///getter pentru raspuns corect
    return raspunsCorect;
}
