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

    Scor() : valoare(0) {}
    ///constructor de init
    Scor(const std::string& n, size_t v) : nume(n), valoare(v) {}

    friend std::ostream& operator<<(std::ostream& os, const Scor& s);
    friend std::istream& operator>>(std::istream& is, Scor& s);
};

class Clasament {
private:
    std::vector<Scor> listaScoruri;
    std::string numeFisier = "clasament.txt";

    Clasament() = default;
    static Clasament* instanta; //design pattern - singleton

    //functie de comparare statica pt std::sort
    static bool comparaScoruri(const Scor& a, const Scor& b);

public:
    //singura met prin care putem obtine obiectul
    static Clasament& getInstanta() {
        if (instanta == nullptr) {
            instanta = new Clasament();
        }
        return *instanta;
    }

    //stergem pos de a copia obiectul
    Clasament(const Clasament&) = delete;
    void operator=(const Clasament&) = delete;

    Clasament(Clasament&& other) noexcept;
    Clasament& operator=(Clasament&& other) noexcept;

    ~Clasament() = default;

    //metode I/O
    void incarca();
    void salveaza() const;

    //metodă de logica
    void adaugaScor(const std::string& nume, size_t scor);
    void afiseaza() const;
};

#endif