#include "../headers/ProfilUtilizator.h"

//destructor
ProfilUtilizator::~ProfilUtilizator() {
}

//constructor de mutare
ProfilUtilizator::ProfilUtilizator(ProfilUtilizator &&other) noexcept
    : numeProfil{std::move(other.numeProfil)},
      highscoreGlobal{other.highscoreGlobal} {
    other.highscoreGlobal = 0;
}

//operator de atribuire prin mutare
ProfilUtilizator &ProfilUtilizator::operator=(ProfilUtilizator &&other) noexcept {
    if (this != &other) {
        //mutam resursele
        numeProfil = std::move(other.numeProfil);
        highscoreGlobal = other.highscoreGlobal;

        //golim sursa
        other.highscoreGlobal = 0;
    }
    return *this;
}

std::string getCaleFisier(const std::string &numeProfil) {
    //inlocuim spatiile sau caracterele cu _ pt a preveni erorile in numele fisierului
    std::string numeCurat = numeProfil;
    std::replace(numeCurat.begin(), numeCurat.end(), ' ', '_');
    return "profil_" + numeCurat + ".dat";
}

void ProfilUtilizator::incarca() {
    std::ifstream fisierIn(getCaleFisier(numeProfil));

    if (fisierIn.is_open()) {
        //citim scorul anterior din fisier
        if (fisierIn >> highscoreGlobal) {
            //scor încărcat cu succes
        } else {
            //daca citirea esueaza, setăm la 0
            highscoreGlobal = 0;
        }
    }
}

void ProfilUtilizator::salveaza() const {
    std::ofstream fisierOut(getCaleFisier(numeProfil));

    if (!fisierOut.is_open()) {
        throw std::runtime_error("Eroare: Nu se poate salva profilul utilizatorului " + numeProfil);
    }

    //salvam doar scorul maxim
    fisierOut << highscoreGlobal;
}

void ProfilUtilizator::actualizeazaHighscore(size_t scorNou) {
    if (scorNou > highscoreGlobal) {
        highscoreGlobal = scorNou;
        std::cout << "\n NOU REACORD PERSONAL! Highscore-ul a fost actualizat la " << highscoreGlobal << " puncte! \n";
        salveaza(); //salveaza imediat dupa actualizare
    } else {
        std::cout << "\nHighscore-ul personal rămâne " << highscoreGlobal << " puncte.\n";
    }
}
