#include "Clasament.h"

Clasament* Clasament::instanta = nullptr;
//implementarea fct de comparare
bool Clasament::comparaScoruri(const Scor& a, const Scor& b) {
    //sorteaza descr
    return a.valoare > b.valoare;
}

void Clasament::incarca() {
    std::ifstream fisierIn(numeFisier);
    listaScoruri.clear();

    if (!fisierIn.is_open()) { //dc fisierul nu exista
        return;
    }

    Scor s_nou("", 0);

    while (fisierIn >> s_nou) {
        listaScoruri.push_back(s_nou);
    }
    //asiguram ca lista este sortata imediat dupa incarcare
    std::sort(listaScoruri.begin(), listaScoruri.end(), comparaScoruri);
}

void Clasament::salveaza() const {
    std::ofstream fisierOut(numeFisier);

    if (!fisierOut.is_open()) {
        throw std::runtime_error("Eroare la salvare: Nu se poate deschide fisierul " + numeFisier);
    }

    for (const Scor& scor : listaScoruri) {
        fisierOut << scor << "\n";
    }
}

void Clasament::adaugaScor(const std::string& nume, size_t scor) {
    //adauga scor, sorteaza si limiteaza lista top 10
    listaScoruri.emplace_back(nume, scor);
    std::sort(listaScoruri.begin(), listaScoruri.end(), comparaScoruri);

    if (listaScoruri.size() > 10) {
        listaScoruri.resize(10);
    }

    salveaza();
}

void Clasament::afiseaza() const {
    std::cout << "\n CLASAMENT TOP 10 \n";
    if (listaScoruri.empty()) {
        std::cout << "Clasamentul este gol.\n";
        return;
    }
    for (size_t i = 0; i < listaScoruri.size(); ++i) {
        std::cout << i + 1 << ". " << listaScoruri[i].nume << " - " << listaScoruri[i].valoare << " puncte\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Scor& s) {
    os << s.valoare << " " << s.nume;
    return os;
}

std::istream& operator>>(std::istream& is, Scor& s) {
    //citim scorul si numele
    is >> s.valoare >> s.nume;
    return is;
}
/*
//constr de mutare
Clasament::Clasament(Clasament&& other) noexcept
    : listaScoruri{std::move(other.listaScoruri)},
      numeFisier{std::move(other.numeFisier)}
{
}

//op de atribuie prin mutare
Clasament& Clasament::operator=(Clasament&& other) noexcept {
    if (this != &other) {
        listaScoruri = std::move(other.listaScoruri);
        numeFisier = std::move(other.numeFisier);
    }
    return *this;
}*/