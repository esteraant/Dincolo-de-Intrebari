#include "../headers/IntrebareRaspunsLiber.h"
#include <cctype>
#include <sstream>
#include <vector>

///schimbam raspunsul utilizatorului sa contina un string doar din caractere de la a-z
std::string ConvertireRaspuns(const std::string &str) {
    std::string sir = "";

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        if (std::isalpha(static_cast<unsigned char>(c)) || c == ' ') {
            sir += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }

    ///eliminam spatiile
    std::string rezultat = "";
    for (size_t i = 0; i < sir.length(); ++i) {
        if (sir[i] != ' ') {
            rezultat += sir[i];
        }
    }

    return rezultat;
}


///constructor
IntrebareRaspunsLiber::IntrebareRaspunsLiber(const std::string &t, const std::vector<std::string> &rC)
    : Intrebare(t, -1) {
    this->raspunsuriCorecte = rC;
}

bool IntrebareRaspunsLiber::verificaRaspunsText(const std::string &raspunsUtilizator) const {
    std::string raspunsUtilizatorNormalizat = ConvertireRaspuns(raspunsUtilizator);
    ///cautam rasp utilizatorului in lista de raspunsuri corecte
    for (const std::string &rCorect: raspunsuriCorecte) {
        std::string raspunsCorectNormalizat = ConvertireRaspuns(rCorect);

        if (raspunsCorectNormalizat == raspunsUtilizatorNormalizat) {
            return true;
        }
    }
    return false;
}

/*bool IntrebareRaspunsLiber::verificaRaspuns(int raspunsUtilizator) const {
    return false;
}*/

int IntrebareRaspunsLiber::calculeazaPunctaj() const {
    return 3;
}

///constructor virtual (Clone)
std::unique_ptr<Intrebare> IntrebareRaspunsLiber::clone() const {
    return std::make_unique<IntrebareRaspunsLiber>(*this);
}

void IntrebareRaspunsLiber::afiseazaDetalii(std::ostream &os) const {
    os << "  (Raspunde in scris)\n";
}

void IntrebareRaspunsLiber::afiseazaTipIntrebare() const {
    std::cout << "Tip: Raspuns Liber.\n";
}
