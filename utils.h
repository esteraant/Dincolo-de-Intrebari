#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <memory>
#include "Intrebare.h"
#include "CapitolPoveste.h"
#include  "Generator.h"

std::vector<std::unique_ptr<Intrebare>> citesteIntrebari(const std::string& numeFisier);
std::vector<CapitolPoveste> citestePovesti(const std::string& numeFisier);
std::string trim(const std::string& str);

#endif
