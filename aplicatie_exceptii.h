#ifndef APLICATIE_EXCEPTII_H
#define APLICATIE_EXCEPTII_H

#include <stdexcept>
#include <string>

// Clasa de bază proprie pentru toate excepțiile din aplicație
class AplicatieExceptie : public std::exception {
protected:
    std::string mesaj;

public:
    // Constructor
    AplicatieExceptie(const std::string& msg) : mesaj{msg} {}

    // Suprascriem metoda what() din std::exception
    virtual const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

// ----------------------------------------------------
// Ierarhia de erori specifice distincte (Clase derivate)
// ----------------------------------------------------


// 1. Eroare de I/O (Citirea fișierelor)
class EroareFisierInexistent : public AplicatieExceptie {
public:
    // Tratează erori la citirea/deschiderea fișierelor
    EroareFisierInexistent(const std::string& nume_fisier)
        : AplicatieExceptie("Eroare I/O: Fisierul '" + nume_fisier + "' nu a putut fi deschis/gasit.") {}
};


// 2. Eroare de Date (Structură invalidă)
class EroareFormatDate : public AplicatieExceptie {
public:
    // Tratează erori structurale (date insuficiente, format greșit)
    EroareFormatDate(const std::string& detalii)
        : AplicatieExceptie("Eroare Format Date: Datele din fisier sunt structurate gresit. Detalii: " + detalii) {}
};


// 3. Eroare Logică (Date insuficiente la runtime)
class EroareDateInsuficiente : public AplicatieExceptie {
public:
    // Tratează erori logice (ex: nu sunt suficiente întrebări pentru a crea nivelele)
    EroareDateInsuficiente(size_t necesar, size_t gasit)
        : AplicatieExceptie("Eroare Logica: Numar insuficient de elemente. Necesar minim: " + std::to_string(necesar) +
                             ", Gasit: " + std::to_string(gasit) + ".") {}
};

#endif // APLICATIE_EXCEPTII_H
