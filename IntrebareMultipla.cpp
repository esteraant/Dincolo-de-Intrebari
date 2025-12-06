#include "IntrebareMultipla.h"
#include <sstream>

// Constructor: apeleaza constructorul clasei de baza (cu -1, deoarece raspunsCorect nu este utilizat)
IntrebareMultipla::IntrebareMultipla(const std::string& t,
                                     const std::vector<std::string>& rP,
                                     const std::set<int>& indiciCorecti)
    // Apelam constructorul Intrebare(text, rC). rC = -1 ca placeholder.
    : Intrebare(t, -1)
{
    this->raspunsuriPosibile = rP;
    this->indiciRaspunsuriCorecte = indiciCorecti;
}

// Implementare verificaRaspuns (Simplificată: verificăm dacă răspunsul introdus face parte din setul corect)
bool IntrebareMultipla::verificaRaspuns(int raspuns_utilizator) const  {
    // Verificam daca indexul introdus de utilizator (1-based) este in setul de indici corecti
    return indiciRaspunsuriCorecte.count(raspuns_utilizator);
}

// NOU: Implementarea obligatorie pentru a rezolva abstractizarea
// Intrebarea Multiplă nu acceptă răspunsuri de tip text liber.
bool IntrebareMultipla::verificaRaspunsText(const std::string& raspuns_utilizator) const  {
    return false;
}

// Implementare Functie virtuala SPECIFICA TEMEI:
int IntrebareMultipla::calculeazaPunctaj() const {
    return 4; // Intrebarile multiple valoreaza cel mai mult
}

// Implementare Constructor Virtual (Clone) - Folosind sintaxa NEW
std::unique_ptr<Intrebare> IntrebareMultipla::clone() const {
    // Creează o copie a obiectului curent (Deep Copy) folosind 'new'
    return std::unique_ptr<Intrebare>(new IntrebareMultipla(*this));
}

// Implementare Afisare Virtuala (Detalii):
void IntrebareMultipla::afiseazaDetalii(std::ostream& os) const {
    for (size_t i = 0; i < raspunsuriPosibile.size(); i++) {
        os << "  " << i + 1 << ") " << raspunsuriPosibile[i] << "\n";
    }
    os << "  (ATENTIE! Exista mai multe variante corecte!)\n";
}

size_t IntrebareMultipla::getNumarOptiuni() const {
    return raspunsuriPosibile.size();
}
