#ifndef APLICATIE_EXCEPTII_H
#define APLICATIE_EXCEPTII_H
/**
 *@brief Base class for all custom exceptions in the application
 *
 */

#include <string>

///clasa de baza
class AplicatieExceptie : public std::exception {
protected:
    std::string mesaj;

public:
    ///constructor
    explicit AplicatieExceptie(const std::string &msg) : mesaj{msg} {
    }

    [[nodiscard]]virtual const char *what() const noexcept override {
        return mesaj.c_str();
    }
};


///eroare citirea fisierelor
class EroareFisierInexistent : public AplicatieExceptie {
public:
    explicit EroareFisierInexistent(const std::string &numeFisier)
        : AplicatieExceptie("Eroare I/O: Fisierul '" + numeFisier + "' nu a putut fi deschis/gasit.") {
    }
};


///eroare la date
class EroareFormatDate : public AplicatieExceptie {
public:
    explicit EroareFormatDate(const std::string &detalii)
        : AplicatieExceptie("Eroare Format Date: Datele din fisier sunt structurate gresit. Detalii: " + detalii) {
    }
};


///eroare logica (date insuficiente)
class EroareDateInsuficiente : public AplicatieExceptie {
public:
    EroareDateInsuficiente(size_t necesar, size_t gasit)
        : AplicatieExceptie("Eroare Logica: Numar insuficient de elemente. Necesar minim: " + std::to_string(necesar) +
                            ", Gasit: " + std::to_string(gasit) + ".") {
    }
};

#endif
