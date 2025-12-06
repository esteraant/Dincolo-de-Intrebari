#ifndef INTREBAREMULTIPLA_H
#define INTREBAREMULTIPLA_H

#include "Intrebare.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <set> // Vom folosi set pentru a gestiona usor raspunsurile corecte

// Raspunsul corect (raspunsCorect) in clasa de baza va fi inutil aici.
// Vom folosi un std::set privat pentru a stoca indicii raspunsurilor corecte.

class IntrebareMultipla : public Intrebare {
private:
    std::vector<std::string> raspunsuriPosibile;
    std::set<int> indiciRaspunsuriCorecte; // Set de indici (1, 3, 5)

public:
    // Constructor: primeste text, optiuni si vectorul de indici corecti (1-based)
    IntrebareMultipla(const std::string& t,
                     const std::vector<std::string>& rP,
                     const std::set<int>& indiciCorecti);

    // Implementarea functiilor virtuale pure:

    // Suprascrie verificaRaspuns() pentru a gestiona raspunsurile multiple.
    // Presupunem ca raspuns_utilizator primeste unul dintre indicii corecti (simplificare)
    // NOTA: Implementarea va verifica daca raspunsul utilizatorului ESTE UNUL dintre cele corecte.
    bool verificaRaspuns(int raspuns_utilizator) const override;
    virtual bool verificaRaspunsText(const std::string& raspuns_utilizator) const override;
    // Functie virtuala SPECIFICA TEMEI:
    int calculeazaPunctaj() const override;

    // Constructor Virtual (Clone):
    std::unique_ptr<Intrebare> clone() const override;

    // Implementare Afisare Virtuala (Detalii):
    void afiseazaDetalii(std::ostream& os) const override;

    // Getter specific pentru numarul de optiuni (ca la Grila)
    size_t getNumarOptiuni() const;
};

#endif // INTREBAREMULTIPLA_H
