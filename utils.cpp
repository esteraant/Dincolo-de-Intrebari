#include "utils.h"
#include "aplicatie_exceptii.h"
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
        int raspuns_corect_unic = 0; ///pt G, A, L
        std::vector<std::string> optiuni; ///pt G, M

        ///linia 2 - intrebarea propriu-zisa
        if (!std::getline(fin, text))
            throw EroareFormatDate("Lipsa text intrebare dupa tipul '" + std::string(1, tipIntrebare) + "'.");

        ///linia 3 - Raspunsul Corect
        if (!std::getline(fin, linie))
            throw EroareFormatDate("Lipsa raspunsului corect (linia 3) dupa intrebarea: '" + text + "'.");


        if (tipIntrebare == 'G' || tipIntrebare == 'A' || tipIntrebare == 'M') {
             raspuns_corect_str = linie;
        } else if (tipIntrebare == 'L') {
            raspuns_corect_str = linie;
        }

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

        if (tipIntrebare == 'G') {
            ///convertim rasp corect citit ca string in int
             std::stringstream(raspuns_corect_str) >> raspuns_corect_unic;
            ///cream dinamic un ob intrebaregrila
             intrebari.push_back(std::make_unique<IntrebareGrila>(text, optiuni, raspuns_corect_unic - 1));
        }
        else if (tipIntrebare == 'A') {
             std::stringstream(raspuns_corect_str) >> raspuns_corect_unic; ///convertim in int
             intrebari.push_back(std::make_unique<IntrebareAdevaratFals>(text, raspuns_corect_unic == 1 ? 1 : 0)); ///cream si 1-A, 0-F
        }
        else if (tipIntrebare == 'L') {
            ///lista de rasp corecte separate prin ;
            std::stringstream ss_raspunsuri(raspuns_corect_str);
            std::string token;
            std::vector<std::string> raspunsuri_libere_corecte; ///vector care stocheaza lista finala
        ///separam stringul folosind ; si umplem vectorul
            while (std::getline(ss_raspunsuri, token, ';')) {
                // Adaugă trim aici pentru a curăța spațiile din răspunsurile libere
                token = trim(token);
                raspunsuri_libere_corecte.push_back(token);
            }
            ///creare obiect raspunsliber
            intrebari.push_back(std::make_unique<IntrebareRaspunsLiber>(text, raspunsuri_libere_corecte));

        }
        else if (tipIntrebare == 'M') {
             std::set<int> indici_multipli; ///stocam indicii corecti
             std::stringstream ss_raspuns(raspuns_corect_str);
             std::string indice_str;
             int indice;

             while (std::getline(ss_raspuns, indice_str, ',')) {
                 // Curățăm spațiile din jurul indicelui
                 indice_str = trim(indice_str);

                 if (std::stringstream(indice_str) >> indice) {
                     indici_multipli.insert(indice);
                 }
             }
             ///daca nu am gasit optiuni
             if (optiuni.empty()) throw EroareFormatDate("Lipsa optiunilor pentru intrebarea multipla.");
             intrebari.push_back(std::make_unique<IntrebareMultipla>(text, optiuni, indici_multipli));

        } else { ///niciun tip de intrebare nu a fost recunoscut
             throw EroareFormatDate("Tip de intrebare necunoscut (" + std::string(1, tipIntrebare) + ") pentru intrebarea: " + text + ".");
        }

        ///sarim peste randul gol separator
        std::getline(fin, linie);
    }

    return intrebari;
}
