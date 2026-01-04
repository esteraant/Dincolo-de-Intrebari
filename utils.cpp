#include "utils.h"
#include "aplicatie_exceptii.h"
#include "Generator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <set>
#include <cctype>

#include "IntrebareGrila.h"
#include "IntrebareAdevaratFals.h"
#include "IntrebareRaspunsLiber.h"
#include "IntrebareMultipla.h"


///functie pt a elimina spatiile albe
std::string trim(const std::string& str) {
    size_t start = 0;
    ///cauta primul car care nu este spatiu
    while (start < str.length() && std::isspace(static_cast<unsigned char>(str[start]))) {
        start++;
    }

    size_t finish = str.length();
    ///cauta ultimul car care nu este spatiu
    while (finish > start && std::isspace(static_cast<unsigned char>(str[finish - 1]))) {
        finish--;
    }

    return str.substr(start, finish - start);
}


///citirea capitolelor de poveste
std::vector<CapitolPoveste> citestePovesti(const std::string& numeFisier) {

    std::ifstream fin(numeFisier);
    std::vector<CapitolPoveste> capitole;

    if (!fin.is_open()) {
        throw EroareFisierInexistent(numeFisier);
    }

    std::string linie;
    int nrCapitole;

    ///citim nr de capitole care se afla pe prima linie
    if (!(fin >> nrCapitole)) {
        throw EroareFormatDate("Nu s-a putut citi numarul de capitole de pe prima linie.");
    }
    ///terminam linia cu numarul de capitole
    std::getline(fin, linie);

    for (int i = 0; i < nrCapitole; i++) {
        std::string titlu, continut_total;

        ///citim titlul
        if (!std::getline(fin, titlu)) {
             throw EroareFormatDate("Fisierul s-a terminat brusc inainte de citirea titlului capitolului " + std::to_string(i + 1) + ".");
        }

        ///citim continutul pana intalnim un rand gol
        while (std::getline(fin, linie) && !linie.empty())
            continut_total += linie + "\n";

        ///cream si adaugam noul obiect CapitolPoveste
        capitole.push_back(CapitolPoveste(titlu, continut_total));
    }
    return capitole;
}

std::vector<std::unique_ptr<Intrebare>> citesteIntrebari(const std::string& numeFisier) {
    std::ifstream fin(numeFisier);
    std::vector<std::unique_ptr<Intrebare>> intrebari;

    if (!fin.is_open()) {
        throw EroareFisierInexistent(numeFisier);
    }

    std::string linie;

    ///sarim peste prima linie care contine nr de intrebari
    std::getline(fin, linie);

    ///citim intrebarile
    while (std::getline(fin, linie)) {
        if (linie.empty()) continue;

        char tipIntrebare = linie[0];

        std::string text;
        std::string raspuns_corect_str; /// ex: G, A, L, M
        int raspuns_corect_unic = 0;
        std::vector<std::string> optiuni;
        std::set<int> indici_multipli;
        std::vector<std::string> raspunsuri_libere_corecte;

        ///linia 2 - intrebarea propriu-zisa
        if (!std::getline(fin, text))
            throw EroareFormatDate("Lipsa text intrebare dupa tipul '" + std::string(1, tipIntrebare) + "'.");

        ///linia 3 - raspunsul corect
        if (!std::getline(fin, linie))
            throw EroareFormatDate("Lipsa raspunsului corect (linia 3) dupa intrebarea: '" + text + "'.");

        raspuns_corect_str = linie;

        /*if (tipIntrebare == 'G' || tipIntrebare == 'A' || tipIntrebare == 'M') {
             raspuns_corect_str = linie;
        } else if (tipIntrebare == 'L') {
            raspuns_corect_str = linie;
        } */

        ///linia 4: optiunile - pentru G si M
        if (tipIntrebare == 'G' || tipIntrebare == 'M') {
             std::string optiuni_str;
             if (!std::getline(fin, optiuni_str))
                 throw EroareFormatDate("Lipsa optiunilor separate prin ';' pentru intrebarea: '" + text + "'.");

             std::stringstream ss(optiuni_str);
             std::string token;

             ///separa fiecare optiune separata de ';'
             while (std::getline(ss, token, ';')) {
                 token = trim(token);
                 ///adaugam optiunea doar daca nu este goala dupa curatare
                 if (!token.empty())
                     optiuni.push_back(token);
             }
          }

        if (tipIntrebare == 'G' || tipIntrebare == 'A') {
            std::stringstream(raspuns_corect_str) >> raspuns_corect_unic;
        }
        else if (tipIntrebare == 'L') {
            std::stringstream ss(raspuns_corect_str);
            std::string token;
            while (std::getline(ss, token, ';')) {
                raspunsuri_libere_corecte.push_back(trim(token));
            }
        }
        else if (tipIntrebare == 'M') {
            std::stringstream ss(raspuns_corect_str);
            std::string indice_str;
            while (std::getline(ss, indice_str, ',')) {
                indici_multipli.insert(std::stoi(trim(indice_str)));
            }
        }
        auto nouaIntrebare = Generator::creeaza(
                   tipIntrebare, text, optiuni, raspuns_corect_unic, indici_multipli, raspunsuri_libere_corecte
               );

        if (nouaIntrebare) {
            intrebari.push_back(std::move(nouaIntrebare));
        } else {
            throw EroareFormatDate("Tip de intrebare necunoscut: " + std::string(1, tipIntrebare));
        }

        std::getline(fin, linie); // sarim peste randul gol separator
    }

    return intrebari;
}
