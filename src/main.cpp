#include "Intrebare.h"
//#include "IntrebareGrila.h"
#include "CapitolPoveste.h"
#include "Nivel.h"
#include "Quiz.h"
#include "utils.h"
#include "aplicatie_exceptii.h"
#include "Clasament.h"
#include "ProfilUtilizator.h"
//#include "Generator.h"
#include "ColectieResurse.h"
#include "UtilitareProgres.h"


#include <iostream>
#include <vector>
#include <string>
//#include <limits>
#include <memory>
#include <utility>


int main() {
    std::vector<std::unique_ptr<Intrebare> > toateIntrebarile;

    ColectieResurse<CapitolPoveste> bibliotecaCapitole;
    ColectieResurse<Nivel> structuraNivele;

    try {
        ///blocl try incapsuleaza toata logica de incarcare a datelor unde pot aparea erori

        toateIntrebarile = citesteIntrebari("intrebari.txt");
        auto vectorCapitole = citestePovesti("poveste.txt");
        for (auto& cap : vectorCapitole) {
            bibliotecaCapitole.adauga(std::move(cap));
        }

        ///definirea cerintelor minime pt a rula aplicatia
        constexpr size_t minIntrebari = 8;
        constexpr size_t minCapitole = 4;

        ///verificam daca s-au incarcat suficiente date; daca nu, aruncam o exceptie
        if (toateIntrebarile.size() < minIntrebari || bibliotecaCapitole.getDimensiune() < minCapitole)
            throw EroareDateInsuficiente(minIntrebari, toateIntrebarile.size());
    }

    ///catch-ul general pentru exceptii
    catch (const AplicatieExceptie &e) {
        std::cout << "\n    EROARE LA INCARCAREA DATELOR    \n";
        std::cout << "DETALII: " << e.what() << "\n";
        std::cout << "Aplicatia nu poate continua. Va rugam verificati fisierele de intrare.\n";
        return 1;
    }
    ///catch-ul de backup pentru orice alta eroare
    catch (const std::exception &e) {
        std::cout << "\n    EROARE NECUNOSCUTA APLICATIE \n";
        std::cout << "DETALII: " << e.what() << "\n";
        return 1;
    }

    ///crearea de nivele
        ///nivelul 1
    std::vector<std::unique_ptr<Intrebare> > intrebariN1;
    intrebariN1.push_back(std::move(toateIntrebarile[0]));
    intrebariN1.push_back(std::move(toateIntrebarile[1]));
    structuraNivele.adauga(Nivel("Nivelul 1", std::move(intrebariN1), bibliotecaCapitole[0]));

    ///nivelul 2
    std::vector<std::unique_ptr<Intrebare> > intrebariN2;
    intrebariN2.push_back(std::move(toateIntrebarile[2]));
    intrebariN2.push_back(std::move(toateIntrebarile[3]));
    structuraNivele.adauga(Nivel("Nivelul 2", std::move(intrebariN2), bibliotecaCapitole[1]));

    ///nivelul 3
    std::vector<std::unique_ptr<Intrebare> > intrebariN3;
    intrebariN3.push_back(std::move(toateIntrebarile[4]));
    intrebariN3.push_back(std::move(toateIntrebarile[5]));
    structuraNivele.adauga(Nivel("Nivelul 3", std::move(intrebariN3), bibliotecaCapitole[2]));

    ///nivelul 4
    std::vector<std::unique_ptr<Intrebare> > intrebariN4;
    intrebariN4.push_back(std::move(toateIntrebarile[6]));
    intrebariN4.push_back(std::move(toateIntrebarile[7]));
    structuraNivele.adauga(Nivel("Nivelul 4", std::move(intrebariN4), bibliotecaCapitole[3]));


    ///verificare constructor/destructor/operator
    ///std::cout << "\n Teste operator si constructor \n";
    /*
        Nivel n_test_copie = lista_nivele[2];
        Nivel n_test_atribuire;
        n_test_atribuire = n_test_copie;
        ///std::cout << "\n";
    */
    //Clasament clasament;
    try {
        Clasament::getInstanta().incarca();
    } catch (const std::exception &e) {
        std::cerr << "Eroare la incarcarea clasamentului: " << e.what() << "\n";
    }

    ///rulare aplicatie
    std::string numeUtilizator;
    std::cout << "Introdu un nume de utilizator: ";
    if (!(std::cin >> numeUtilizator)) {
        numeUtilizator = "Anonim";
    }

    ProfilUtilizator profil(numeUtilizator); //creeaza obiectul
    profil.incarca(); //incarca highscore-ul anterior

    std::cout << "\n\n";
    std::cout << "Profil incarcat pentru utilizatorul: " << profil.getNumeProfil() << "\n";
    std::cout << "Highscore-ul tau anterior este: "
            << profil.getHighscoreGlobal() << " puncte.\n\n";
    ///mutarea vectorului de nivele in Quiz
    std::vector<Nivel> vectorPtQuiz;
    for(size_t i = 0; i < structuraNivele.getDimensiune(); ++i) {
        vectorPtQuiz.push_back(structuraNivele[i]);
    }

    Quiz quiz(numeUtilizator, std::move(vectorPtQuiz));
    quiz.aplicatie();
    std::cout << quiz;

    size_t scorFinal = quiz.getScorTotal();

    //actualizare profil personal
    profil.actualizeazaHighscore(scorFinal);

    //actualizare clasament global
    Clasament::getInstanta().adaugaScor(numeUtilizator, scorFinal);
    Clasament::getInstanta().afiseaza();


    ///testare
    //std::cout << "\n Testare Getters si Polimorfism \n";
    //if (quiz.get_nivele().size() > 0) {
        /*const Intrebare& prima_intrebare = quiz.get_nivele()[0].getIntrebare(0);
        std::cout << "Titlu Intrebare: " << prima_intrebare.getText() << "\n";
        std::cout << "Punctaj: " << prima_intrebare.calculeazaPunctaj() << "\n";

        ///verificare dynamic_cast
        IntrebareGrila* grila_ptr = dynamic_cast<IntrebareGrila*>(const_cast<Intrebare*>(&prima_intrebare));
        if (grila_ptr)
                 std::cout << "Numar Optiuni (Grila): " << grila_ptr->getNumarOptiuni() << "\n";
        std::cout << "Titlu Capitol (Nivel 1): " << quiz.get_nivele()[0].getCapitol().getTitlu() << "\n";
        */
    //}

    std::cout << "\n STATISTICI FINALE \n";

    // Function Template pe Nivele
    double progresJoc = calculeazaProgresul(structuraNivele);
    std::cout << "Nivele finalizate: " << progresJoc << "%\n";

    // Function Template pe Capitole
    double progresPoveste = calculeazaProgresul(bibliotecaCapitole);
    std::cout << "Poveste descoperita: " << progresPoveste << "%\n";
    std::cout << "\n";
    return 0;
}
