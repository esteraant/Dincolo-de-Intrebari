#include "utils.h"
#include "aplicatie_exceptii.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <set>

// Includem clasele derivate pentru instantiere polimorfica
#include "IntrebareGrila.h"
#include "IntrebareAdevaratFals.h"
#include "IntrebareRaspunsLiber.h"
#include "IntrebareMultipla.h" // NOU: Clasa derivata suplimentara


// Funcție pentru citirea capitolelor de poveste
std::vector<CapitolPoveste> citestePovesti(const std::string& numeFisier) {

    std::ifstream fin(numeFisier);
    std::vector<CapitolPoveste> capitole;

    if (!fin.is_open()) {
        // ARUNCA EXCEPȚIA 1: Eroare de I/O
        throw EroareFisierInexistent(numeFisier);
    }

    std::string linie;
    int nrCapitole;

    // citim nr de capitole care se afla pe prima linie
    if (!(fin >> nrCapitole)) {
        // ARUNCA EXCEPȚIA 2: Eroare de Format
        throw EroareFormatDate("Nu s-a putut citi numarul de capitole de pe prima linie.");
    }
    // terminam linia cu numarul de cap
    std::getline(fin, linie);

    for (int i = 0; i < nrCapitole; i++) {
        std::string titlu, continut_total;

        // citim titlul
        if (!std::getline(fin, titlu)) {
             throw EroareFormatDate("Fisierul s-a terminat brusc inainte de citirea titlului capitolului " + std::to_string(i + 1) + ".");
        }

        // citim continutul pana intalnim un rand gol
        while (std::getline(fin, linie) && !linie.empty())
            continut_total += linie + "\n";

        // cream si adaugam noul obiect CapitolPoveste
        capitole.emplace_back(titlu, continut_total);
    }
    return capitole;
}


// Funcție pentru citirea întrebărilor
// utils.cpp (Funcția citesteIntrebari - Logica NOUA de citire L)

std::vector<std::unique_ptr<Intrebare>> citesteIntrebari(const std::string& numeFisier) {
    std::ifstream fin(numeFisier);
    std::vector<std::unique_ptr<Intrebare>> intrebari;

    if (!fin.is_open()) {
        throw EroareFisierInexistent(numeFisier);
    }

    std::string linie;

    // sarim peste prima linie care contine nr de intrebari
    std::getline(fin, linie);

    // citim intrebarile
    while (std::getline(fin, linie)) {
        if (linie.empty()) continue;

        char tipIntrebare = linie[0];

        std::string text;
        std::string raspuns_corect_str; // Va stoca fie numar (pentru G, A, L), fie string (pentru M)
        int raspuns_corect_unic = 0; // Pentru tipurile G, A, L
        std::vector<std::string> optiuni; // Pentru tipurile G, M

        // linia 2 - intrebarea propriu-zisa
        if (!std::getline(fin, text))
            throw EroareFormatDate("Lipsa text intrebare dupa tipul '" + std::string(1, tipIntrebare) + "'.");

        // Linia 3 - Raspunsul Corect (Formatul depinde de tip)
        if (!std::getline(fin, linie))
            throw EroareFormatDate("Lipsa raspunsului corect (linia 3) dupa intrebarea: '" + text + "'.");


        if (tipIntrebare == 'G' || tipIntrebare == 'A' || tipIntrebare == 'M') {
             // Raspuns numeric/indici (se citeste raspuns_corect_str si se parseaza mai jos)
             raspuns_corect_str = linie;
        } else if (tipIntrebare == 'L') {
            // NOU: Raspuns Liber (Lista de string-uri separate prin ;)
            raspuns_corect_str = linie;
        }

        // Linia 4: Optiunile (necesare pentru G si M)
        if (tipIntrebare == 'G' || tipIntrebare == 'M') {
             std::string optiuni_str;
             if (!std::getline(fin, optiuni_str))
                 throw EroareFormatDate("Lipsa optiunilor separate prin ';' pentru intrebarea: '" + text + "'.");

             std::stringstream ss(optiuni_str);
             std::string token;
             while (std::getline(ss, token, ';')) {
                 size_t first = token.find_first_not_of(' ');
                 size_t last = token.find_last_not_of(' ');
                 if (std::string::npos != first) {
                     token = token.substr(first, (last - first + 1));
                 }
                 optiuni.push_back(token);
             }
        }

        // LOGICA DE CREARE A OBIECTULUI
        if (tipIntrebare == 'G') {
             std::stringstream(raspuns_corect_str) >> raspuns_corect_unic;
             intrebari.push_back(std::make_unique<IntrebareGrila>(text, optiuni, raspuns_corect_unic - 1));
        } else if (tipIntrebare == 'A') {
             std::stringstream(raspuns_corect_str) >> raspuns_corect_unic;
             intrebari.push_back(std::make_unique<IntrebareAdevaratFals>(text, raspuns_corect_unic == 1 ? 1 : 0));
        } else if (tipIntrebare == 'L') {
            // NOU: Parsam lista de raspunsuri text corecte
            std::stringstream ss_raspunsuri(raspuns_corect_str);
            std::string token;
            std::vector<std::string> raspunsuri_libere_corecte;
            while (std::getline(ss_raspunsuri, token, ';')) {
                raspunsuri_libere_corecte.push_back(token);
            }
            // Creare obiect Raspuns Liber
            intrebari.push_back(std::make_unique<IntrebareRaspunsLiber>(text, raspunsuri_libere_corecte));

        } else if (tipIntrebare == 'M') {
             std::set<int> indici_multipli;
             std::stringstream ss_raspuns(raspuns_corect_str);
             std::string indice_str;
             int indice;

             while (std::getline(ss_raspuns, indice_str, ',')) {
                 if (std::stringstream(indice_str) >> indice) {
                     indici_multipli.insert(indice);
                 }
             }
             if (optiuni.empty()) throw EroareFormatDate("Lipsa optiunilor pentru intrebarea multipla.");
             intrebari.push_back(std::make_unique<IntrebareMultipla>(text, optiuni, indici_multipli));

        } else {
             throw EroareFormatDate("Tip de intrebare necunoscut ('" + std::string(1, tipIntrebare) + "') pentru intrebarea: '" + text + "'.");
        }

        // sarim peste randul gol separator
        std::getline(fin, linie);
    }

    return intrebari;
}
