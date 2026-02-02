#include "../headers/utils.h"
#include "../headers/aplicatie_exceptii.h"
#include "../headers/Generator.h"
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <set>
#include <cctype>

///functie pt a elimina spatiile albe
std::string trim(const std::string &str) {
    size_t start = 0;
    while (start < str.length() && std::isspace(static_cast<unsigned char>(str[start]))) {
        start++;
    }

    size_t finish = str.length();
    while (finish > start && std::isspace(static_cast<unsigned char>(str[finish - 1]))) {
        finish--;
    }

    return str.substr(start, finish - start);
}


///citirea capitolelor de poveste
std::vector<CapitolPoveste> citestePovesti(const std::string &numeFisier) {
    std::ifstream fin(numeFisier);
    std::vector<CapitolPoveste> capitole;

    if (!fin.is_open()) {
        throw EroareFisierInexistent(numeFisier);
    }

    std::string linie;
    int nrCapitole;

    if (!(fin >> nrCapitole)) {
        throw EroareFormatDate("Nu s-a putut citi numarul de capitole de pe prima linie.");
    }
    std::getline(fin, linie);

    for (int i = 0; i < nrCapitole; i++) {
        std::string titlu, continutTotal;

        if (!std::getline(fin, titlu)) {
            throw EroareFormatDate(
                "Fisierul s-a terminat brusc inainte de citirea titlului capitolului " + std::to_string(i + 1) + ".");
        }

        while (std::getline(fin, linie) && !linie.empty())
            continutTotal += linie + "\n";

        capitole.push_back(CapitolPoveste(titlu, continutTotal));
    }
    return capitole;
}

std::vector<std::unique_ptr<Intrebare> > citesteIntrebari(const std::string &numeFisier) {
    std::ifstream fin(numeFisier);
    std::vector<std::unique_ptr<Intrebare> > intrebari;

    if (!fin.is_open()) {
        throw EroareFisierInexistent(numeFisier);
    }

    std::string linie;

    std::getline(fin, linie);

    while (std::getline(fin, linie)) {
        if (linie.empty()) continue;

        char tipIntrebare = linie[0];

        std::string text;
        std::string raspunsCorectStr; /// ex: G, A, L, M
        int raspunsCorectUnic = 0;
        std::vector<std::string> optiuni;
        std::set<int> indiciMultipli;
        std::vector<std::string> raspunsuriLibereCorecte;

        if (!std::getline(fin, text))
            throw EroareFormatDate("Lipsa text intrebare dupa tipul '" + std::string(1, tipIntrebare) + "'.");

        if (!std::getline(fin, linie))
            throw EroareFormatDate("Lipsa raspunsului corect (linia 3) dupa intrebarea: '" + text + "'.");

        raspunsCorectStr = linie;

        /*if (tipIntrebare == 'G' || tipIntrebare == 'A' || tipIntrebare == 'M') {
             raspuns_corect_str = linie;
        } else if (tipIntrebare == 'L') {
            raspuns_corect_str = linie;
        } */

        if (tipIntrebare == 'G' || tipIntrebare == 'M') {
            std::string optiuniStr;
            if (!std::getline(fin, optiuniStr))
                throw EroareFormatDate("Lipsa optiunilor separate prin ';' pentru intrebarea: '" + text + "'.");

            std::stringstream ss(optiuniStr);
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
            std::stringstream(raspunsCorectStr) >> raspunsCorectUnic;
        } else if (tipIntrebare == 'L') {
            std::stringstream ss(raspunsCorectStr);
            std::string token;
            while (std::getline(ss, token, ';')) {
                raspunsuriLibereCorecte.push_back(trim(token));
            }
        } else if (tipIntrebare == 'M') {
            std::stringstream ss(raspunsCorectStr);
            std::string indiceStr;
            while (std::getline(ss, indiceStr, ',')) {
                indiciMultipli.insert(std::stoi(trim(indiceStr)));
            }
        }
        auto nouaIntrebare = Generator::creeaza(
            tipIntrebare, text, optiuni, raspunsCorectUnic, indiciMultipli, raspunsuriLibereCorecte
        );

        if (nouaIntrebare) {
            intrebari.push_back(std::move(nouaIntrebare));
        } else {
            throw EroareFormatDate("Tip de intrebare necunoscut: " + std::string(1, tipIntrebare));
        }

        std::getline(fin, linie);
    }

    return intrebari;
}
