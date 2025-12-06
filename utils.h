#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <memory>
#include "Intrebare.h"
#include "CapitolPoveste.h"

// Funcția returnează un vector de pointeri inteligenți (obiecte polimorfice)
std::vector<std::unique_ptr<Intrebare>> citesteIntrebari(const std::string& numeFisier);

// Funcție pentru citirea capitolelor de poveste
std::vector<CapitolPoveste> citestePovesti(const std::string& numeFisier);

#endif // UTILS_H
