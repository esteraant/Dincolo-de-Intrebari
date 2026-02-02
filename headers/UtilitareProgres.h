#ifndef UTILITAREPROGRES_H
#define UTILITAREPROGRES_H

#include <iostream>
#include <vector>
#include "ColectieResurse.h"

/**
* @brief Template function that calculates the percentage of active items in a collection.
* * For questions: how many are correct.
* * For story: how many are unlocked.
 */
template <typename T>
double calculeazaProgresul(const ColectieResurse<T>& colectie) {
    if (colectie.getDimensiune() == 0) return 0.0;

    int contor = 0;
    for (size_t i = 0; i < colectie.getDimensiune(); ++i) {
        if (colectie[i].esteFinalizat()) {
            contor++;
        }
    }
    return (static_cast<double>(contor) / colectie.getDimensiune()) * 100.0;
}

#endif