#include "IntrebareRaspunsLiber.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>

///schimbam raspunsul utilizatorului sa contina un string doar din caractere de la a-z
std::string ConvertireRaspuns(const std::string& str) {
    std::string sir = "";

    for (size_t i = 0; i < str.length(); i++) { ///momentan pastram spatiile
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
IntrebareRaspunsLiber::IntrebareRaspunsLiber(const std::string& t, const std::vector<std::string>& rC)
    : Intrebare(t, -1)
{
    this->raspunsuriCorecte = rC;
}

bool IntrebareRaspunsLiber::verificaRaspunsText(const std::string& raspuns_utilizator) const {

    std::string raspuns_utilizator_normalizat = ConvertireRaspuns(raspuns_utilizator);
    ///cautam rasp utilizatorului in lista de raspunsuri corecte
    for (const std::string& raspuns_corect : raspunsuriCorecte) {
        std::string raspuns_corect_normalizat = ConvertireRaspuns(raspuns_corect);

        if (raspuns_corect_normalizat == raspuns_utilizator_normalizat) {
            return true;
        }
    }
    return false;
}

bool IntrebareRaspunsLiber::verificaRaspuns(int raspuns_utilizator) const {
    return false;
}

int IntrebareRaspunsLiber::calculeazaPunctaj() const {
    return 3;
}

///constructor virtual (Clone)
std::unique_ptr<Intrebare> IntrebareRaspunsLiber::clone() const {
    return std::make_unique<IntrebareRaspunsLiber>(*this);
}

void IntrebareRaspunsLiber::afiseazaDetalii(std::ostream& os) const {
    os << "  (Raspunde in scris)\n";
}
