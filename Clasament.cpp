#include "Clasament.h"

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

    std::string nume;
    size_t scor;

    while (fisierIn >> scor >> nume) {
        listaScoruri.emplace_back(nume, scor);
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
        fisierOut << scor.valoare << " " << scor.nume << "\n";
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