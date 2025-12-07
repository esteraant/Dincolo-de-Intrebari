#include "Intrebare.h"
#include "IntrebareGrila.h" ///folosim pentru dynamic_cast
#include "CapitolPoveste.h"
#include "Nivel.h"
#include "Quiz.h"
#include "utils.h"
#include "aplicatie_exceptii.h"
#include "Clasament.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>
#include <utility>

///functii
std::vector<std::unique_ptr<Intrebare>> citesteIntrebari(const std::string& numeFisier);
std::vector<CapitolPoveste> citestePovesti(const std::string& numeFisier);


int main() {

    std::vector<std::unique_ptr<Intrebare>> toateIntrebarile;
    std::vector<CapitolPoveste> toateCapitolele;

    try {  ///blocl try incapsuleaza toata logica de incarcare a datelor unde pot aparea erori

        toateIntrebarile = citesteIntrebari("intrebari.txt");
        toateCapitolele = citestePovesti("poveste.txt");

        ///definirea cerintelor minime pt a rula aplicatia
        const size_t min_intrebari = 8;
        const size_t min_capitole = 4;

        ///verificam daca s-au incarcat suficiente date; daca nu, aruncam o exceptie
        if (toateIntrebarile.size() < min_intrebari || toateCapitolele.size() < min_capitole)
            throw EroareDateInsuficiente(min_intrebari, toateIntrebarile.size());

    }

    ///catch-ul general pentru exceptii
    catch (const AplicatieExceptie& e) {
        std::cout << "\n    EROARE LA INCARCAREA DATELOR    \n";
        std::cout << "DETALII: " << e.what() << "\n";
        std::cout << "Aplicatia nu poate continua. Va rugam verificati fisierele de intrare.\n";
        return 1;
    }
    ///catch-ul de backup pentru orice alta eroare
    catch (const std::exception& e) {
        std::cout << "\n    EROARE NECUNOSCUTA APLICATIE \n";
        std::cout << "DETALII: " << e.what() << "\n";
        return 1;
    }

    ///initializare si rulare
    std::vector<Nivel> lista_nivele;

    ///crearea de nivele
        ///nivelul 1
    std::vector<std::unique_ptr<Intrebare>> intrebari_n1;
    intrebari_n1.push_back(std::move(toateIntrebarile[0]));
    intrebari_n1.push_back(std::move(toateIntrebarile[1]));
    lista_nivele.emplace_back("Nivelul 1", std::move(intrebari_n1), toateCapitolele[0]);

        ///nivelul 2
    std::vector<std::unique_ptr<Intrebare>> intrebari_n2;
    intrebari_n2.push_back(std::move(toateIntrebarile[2]));
    intrebari_n2.push_back(std::move(toateIntrebarile[3]));
    lista_nivele.emplace_back("Nivelul 2", std::move(intrebari_n2), toateCapitolele[1]);

        ///nivelul 3
    std::vector<std::unique_ptr<Intrebare>> intrebari_n3;
    intrebari_n3.push_back(std::move(toateIntrebarile[4]));
    intrebari_n3.push_back(std::move(toateIntrebarile[5]));
    lista_nivele.emplace_back("Nivelul 3", std::move(intrebari_n3), toateCapitolele[2]);

        ///nivelul 4
    std::vector<std::unique_ptr<Intrebare>> intrebari_n4;
    intrebari_n4.push_back(std::move(toateIntrebarile[6]));
    intrebari_n4.push_back(std::move(toateIntrebarile[7]));
    lista_nivele.emplace_back("Nivelul 4", std::move(intrebari_n4), toateCapitolele[3]);


    ///verificare constructor/destructor/operator
    ///std::cout << "\n Teste operator si constructor \n";
/*
    Nivel n_test_copie = lista_nivele[2];
    Nivel n_test_atribuire;
    n_test_atribuire = n_test_copie;
    ///std::cout << "\n";
*/
    Clasament clasament;
    try {
        clasament.incarca();
    } catch (const std::exception& e) {
        std::cerr << "Eroare la incarcarea clasamentului: " << e.what() << "\n";
    }

    ///rulare aplicatie
    std::string numeUtilizator;
    std::cout << "Introdu un nume de utilizator: ";
    if (!(std::cin >> numeUtilizator)) {
        numeUtilizator = "Anonim";
    }

    ///mutarea vectorului de nivele în Quiz
    Quiz quiz(numeUtilizator, std::move(lista_nivele));
    quiz.aplicatie();
    std::cout << quiz;

    size_t scorFinal = quiz.getScorTotal();
    clasament.adaugaScor(numeUtilizator, scorFinal);
    clasament.afiseaza();

    ///testare
    std::cout << "\n Testare Getters si Polimorfism \n";
    if (quiz.get_nivele().size() > 0) {
        /*const Intrebare& prima_intrebare = quiz.get_nivele()[0].getIntrebare(0);
        std::cout << "Titlu Intrebare: " << prima_intrebare.getText() << "\n";
        std::cout << "Punctaj: " << prima_intrebare.calculeazaPunctaj() << "\n";

        ///verificare dynamic_cast
        IntrebareGrila* grila_ptr = dynamic_cast<IntrebareGrila*>(const_cast<Intrebare*>(&prima_intrebare));
        if (grila_ptr)
                 std::cout << "Numar Optiuni (Grila): " << grila_ptr->getNumarOptiuni() << "\n";
        std::cout << "Titlu Capitol (Nivel 1): " << quiz.get_nivele()[0].getCapitol().getTitlu() << "\n";
        */
    }

    return 0;
}
