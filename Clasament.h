#ifndef CLASAMENT_H
#define CLASAMENT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

struct Scor {
    std::string nume;
    size_t valoare;

    Scor() = default;
    ///constructor de init
    Scor(const std::string& n, size_t v) : nume(n), valoare(v) {}
};

class Clasament {
private:
    std::vector<Scor> listaScoruri;
    const std::string numeFisier = "clasament.txt";

    //functie de comparare statica pt std::sort
    static bool comparaScoruri(const Scor& a, const Scor& b);

public:
    Clasament() = default;

    //metode I/O
    void incarca();
    void salveaza() const;

    //metodă de logica
    void adaugaScor(const std::string& nume, size_t scor);
    void afiseaza() const;
};

#endif