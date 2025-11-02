#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

class Intrebare{
private:
    std::string text;
    std::vector<std::string> raspunsuriPosibile;
    int raspunsCorect;
public:
    Intrebare(const std::string& t, const std::vector<std::string>& rP, int rC)
    {
        this->text = t;
        this->raspunsuriPosibile = rP;
        this->raspunsCorect = rC;
    }
    Intrebare() : raspunsCorect{-1} {} // constructor default

    ~Intrebare()  = default; //destructor

    bool verificaRaspuns(int raspuns_utilizator) const {
        return (raspuns_utilizator - 1) == raspunsCorect;
    }

    int getraspunsCorectIndex() const { //getter pentru raspuns corect
        return raspunsCorect;
    }

    const std::string& getText() const {  //getter pt text
        return text;
    }

    size_t getNumarOptiuni() const { //getter nr de optiuni
        return raspunsuriPosibile.size();
    }

    //operator<<
    friend std::ostream& operator<<(std::ostream& os, const Intrebare& intrebare) {
        os  << intrebare.text << "\n";
        for (size_t i = 0; i < intrebare.raspunsuriPosibile.size(); i++) {
            os << "  " << i + 1 << ") " << intrebare.raspunsuriPosibile[i] << "\n";
        }
        return os;
    }
};


class CapitolPoveste{
private:
    std::string titlu;
    std::string continut;
    bool deblocat;

public:
    CapitolPoveste(const std::string& titlu, const std::string& continut) : deblocat{false} //construtor de init
    {
        this->titlu = titlu;
        this->continut = continut;
        std::cout << "Capitolul " << titlu << " a fost creat.\n";
    }

    CapitolPoveste() : deblocat{false} {} //constructor default
    ~CapitolPoveste() = default; //destructor

    void deblocheaza() {
        this->deblocat = true;
    }

    bool esteDeblocat() const { //getter pt statusul deblocat
        return deblocat;
    }

    const std::string& getTitlu() const { //getter pt titlu
        return titlu;
    }

    //operator<<
    friend std::ostream& operator<<(std::ostream& os, const CapitolPoveste& cap) {
        os<< "~      " << cap.titlu << "     ~\n";
        if (cap.deblocat) {
            os<<cap.continut << "\n";
        }
        else{
            os<<"Capitol blocat. Raspunde corect la intrebari pentru a-l debloca.\n";
        }
        return os;
    }
};


class Nivel{
private:
    std::string numeNivel;
    std::vector<Intrebare> intrebari;
    CapitolPoveste poveste;
    bool nivelPromovat;

public:

    Nivel(const std::string& nume, const std::vector<Intrebare>& intrebari_, const CapitolPoveste& poveste_)
        : nivelPromovat{false}
    {
        this->numeNivel = nume;
        this->intrebari = intrebari_;
        this->poveste = poveste_;
    }

    Nivel() : nivelPromovat{false} {}

    //constructor de copiere
    Nivel(const Nivel& nivel)
        : nivelPromovat{nivel.nivelPromovat}
    {
        std::cout << "Nivel " << nivel.numeNivel << " copiat.\n";
        this->numeNivel = nivel.numeNivel;
        this->intrebari = nivel.intrebari;
        this->poveste = nivel.poveste;
    }

    //operator de atribuire
    Nivel& operator=(const Nivel& nivel) {
        std::cout << "Atribuire Nivel " << nivel.numeNivel << ".\n";

        if (this != &nivel) {
            this->numeNivel = nivel.numeNivel;
            this->intrebari = nivel.intrebari;
            this->poveste = nivel.poveste;
            this->nivelPromovat = nivel.nivelPromovat;
        }
        return *this;
    }

    //destructor
    ~Nivel() {
        std::cout << "Nivel " << numeNivel << " distrus.\n";
    }


    //rularea testului
    void ruleaza_test();

    // getter pt numeNivel (in loc de idNivel)
    const std::string& getNumeNivel() const {
        return numeNivel;
    }

    bool estePromovat() const {
        return nivelPromovat;
    }

    //operator<<
    friend std::ostream& operator<<(std::ostream& os, const Nivel& niv) {
        os << "\n=== Nivel " << niv.numeNivel << " ===\n";
        os << "Status: " ;
        if(niv.nivelPromovat ==1) os << "PROMOVAT" ;
        else os << "NEPROMOVAT";
        os << "\n";
        os << "Intrebari: " << niv.intrebari.size() << "\n";
        os << niv.poveste;
        return os;
    }
};


void Nivel::ruleaza_test() {
    int raspuns_utilizator;

    std::cout << "\n " << numeNivel << " \n";
    std::cout << "Raspunde corect la fiecare intrebare pentru a continua!\n";

    for (size_t i = 0; i < intrebari.size(); i++) {
        const Intrebare& intrebare = intrebari[i];
        bool corect = false;

        //se executa pana cand utilizatorul raspunde corect
        while (!corect) {
            std::cout << "\n" << intrebare;
            std::cout << "Raspunsul tau (nr optiune): ";
            if (!(std::cin >> raspuns_utilizator)) {
            //curatare buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Intrare invalida! Incearca din nou.\n";
            continue;
            }
            if (intrebare.verificaRaspuns(raspuns_utilizator)) {
                std::cout << "Raspuns CORECT!\n";
                corect = true;
            }
            else {
                std::cout << "\n Raspuns GRESIT! \n";
                std::cout << "Incearca din nou.\n";
            }
        }
    }
    //dupa ce a raspuns corect la toate intrebarile
    this->poveste.deblocheaza();
    this->nivelPromovat = true;
    std::cout << "\n FELICITARI! Capitol deblocat! \n";
    std::cout << this->poveste;

}


class Quiz {
private:
    std::vector<Nivel> nivele;
    std::string numeUtilizator;

public:
    Quiz(const std::vector<Nivel>& niv, const std::string& nume) {
        this->nivele = niv;
        this->numeUtilizator = nume;

    }
    void aplicatie() {
        std::cout << "\nBun venit, " << numeUtilizator << "!\n";
        size_t i=0; int raspuns;
        while (i < nivele.size()) {
            Nivel& nivel = nivele[i];
            if (!nivel.estePromovat()) { //verific daca nivelul este mai intai promovat
                nivel.ruleaza_test();
            }
            if (i == nivele.size() - 1) {
                std::cout << "\n FELICITARI!! Ai deblocat toate capitolele!! \n";
                break; //end while
            }
            std::cout <<"\n\n";
            std::cout << "Vrei sa continui la Nivelul " << i + 2 << "? (1/0): ";
            if (!(std::cin >> raspuns)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                raspuns = 0; // Presupunem NU
            }
            //utilizatorul decide daca doreste sa continue cu nivelul urmator
            if (raspuns == 1) {
                i++;
            }
            else {
                std::cout << "\nAplicatia se opreste. Sper ca ai avut o experienta placuta!\n";
                return;
            }
        }
    }
    // operator<<
    friend std::ostream& operator<<(std::ostream& os, const Quiz& qa) {
        os << "\nRaport final pentru " << qa.numeUtilizator << ":\n";
        for (const auto& nivel : qa.nivele) {
            os << nivel;
        }
        return os;
    }
};


std::vector<CapitolPoveste> citestePovesti(const std::string& numeFisier) {

    std::ifstream fin(numeFisier);
    std::vector<CapitolPoveste> capitole;

    if (!fin.is_open()) {
        std::cerr << "Eroare: nu s-a putut deschide fisierul " << numeFisier << "\n";
        return capitole;
    }

    std::string linie;

    //citim nr de capitole care se afla pe prima linie
    int nrCapitole;
    if (!(fin >> nrCapitole)) {
         std::cerr << "Eroare: nu s-a putut citi numarul de capitole.\n";
         return capitole;
    }
    //terminam linia cu numarul
    std::getline(fin, linie);

    for (int i = 0; i < nrCapitole; i++) {
        std::string titlu, continut_total;
        //citim tilul care e pe o singura linie
        if (!std::getline(fin, titlu)) break;

        //citim continutul pana intalnim un rand gol, care marcheaza sfarsitul cap
        while (std::getline(fin, linie) && !linie.empty())
            continut_total += linie + "\n";

        // eliminam  '\n' final adăugat în plus
        if (!continut_total.empty()) {
            continut_total.pop_back();
        }

        //cream si adaugam noul obiect CapitolPoveste
        capitole.emplace_back(titlu, continut_total);
    }
    return capitole;
}


std::vector<Intrebare> citesteIntrebari(const std::string& numeFisier) {
    std::ifstream fin(numeFisier);
    std::vector<Intrebare> intrebari;

    if (!fin.is_open()) {
        std::cerr << "Eroare: nu s-a putut deschide fisierul" << numeFisier << "\n";
        return intrebari;
    }

    std::string linie;

    //sarim peste prima linie care contine nr de intrebari
    std::getline(fin, linie);

    //citim intrebarile
    while (std::getline(fin, linie)) {
        if (linie.empty()) continue; //sarim peste liniile goale

        std::string text, optiuni_str;
        int raspuns_corect_index=0;

        //pima linie - intrebarea
        text = linie;

        // linia 2 - raspunsul corect
        if (!std::getline(fin, linie) || !(std::stringstream(linie) >> raspuns_corect_index)) break;

        // linia 3 optiunile separate prin ;
        if (!std::getline(fin, optiuni_str)) break;

        std::vector<std::string> optiuni;
        std::stringstream ss(optiuni_str);
        std::string token;
        while (std::getline(ss, token, ';')) {
            optiuni.push_back(token);
        }

        //adaugam obiectul Intrebare
        intrebari.emplace_back(text, optiuni, raspuns_corect_index - 1);

        //sarim peste randul gol separator
        std::getline(fin, linie);
    }

    return intrebari;
}

int main() {
    //incarcam datele din fisiere
    std::vector<Intrebare> toateIntrebarile = citesteIntrebari("intrebari.txt");
    std::vector<CapitolPoveste> toateCapitolele = citestePovesti("poveste.txt");

    if (toateIntrebarile.empty() || toateCapitolele.empty()) {
        std::cerr << "\nEroare: Nu s-au putut incarca intrebarile sau capitolele din fisiere.\n";
        return 1;
    }

    //impartirea datelor in nivele: 2 intrebari pentru un capitol din poveste
    Nivel n1("Nivelul 1",
             {toateIntrebarile[0], toateIntrebarile[1]},
             toateCapitolele[0]);
    Nivel n2("Nivelul 2",
             {toateIntrebarile[2], toateIntrebarile[3]},
             toateCapitolele[1]);
    Nivel n3("Nivelul 3",
             {toateIntrebarile[4], toateIntrebarile[5]},
             toateCapitolele[2]);
    Nivel n4("Nivelul 4",
             {toateIntrebarile[6], toateIntrebarile[7]},
             toateCapitolele[3]);

    std::vector<Nivel> lista_nivele = {n1, n2, n3, n4};


    //verificare constructor/destructor/operator
    std::cout << "\n Teste operator si constructor \n";
    Nivel n1_copie = n1; //constr de copiere
    Nivel n2_copie;
    n2_copie = n2; //op de atribuire
    std::cout << "\n";


    //rulare aplicatie quiz
    std::string numeUtilizator;
    std::cout << "Introdu un nume de utilizator: ";
    std::getline(std::cin, numeUtilizator);
    Quiz aplicator(lista_nivele, numeUtilizator);
    aplicator.aplicatie();

    std::cout << aplicator;

    return 0;
}
