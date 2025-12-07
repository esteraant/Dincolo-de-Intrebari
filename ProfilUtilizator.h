#ifndef PROFILUTILIZATOR_H
#define PROFILUTILIZATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>

class ProfilUtilizator {
private:
    std::string numeProfil;
    size_t highscoreGlobal = 0;
    const std::string numeFisierBaza = "profil_"; //numele profilului va fi adăugat dupa _

    void salveaza() const; //salvare a starii curente

public:
    //constructor de init
    ProfilUtilizator(const std::string& nume) : numeProfil(nume) {}

    //metode de I/O
    void incarca();
    //metoda de logica
    void actualizeazaHighscore(size_t scorNou);

    //getteri
    const std::string& getNumeProfil() const { return numeProfil; }
    size_t getHighscoreGlobal() const { return highscoreGlobal; }
};

#endif