#ifndef INTREBARE_H
#define INTREBARE_H

/**
 * @brief Abstract base class representing a generic quiz question.
 * This class serves as the foundation for all question types (Grila, Multipla, etc.).
 */

#include <iostream>
#include <string>
#include <memory>

///clasa de baza
class Intrebare {
private:
    std::string text;
    static size_t nrIntrebariTotale;

protected: /// protected pentru a fi accesibile claselor derivate
    int raspunsCorect;

public:
    ///constructor de baza
    Intrebare(const std::string &t, int rC);

    ///constructor default
    Intrebare() : raspunsCorect{-1} {
    }

    virtual ~Intrebare() = default;

    [[nodiscard]]virtual bool verificaRaspuns(int raspunsUtilizator) const {
        static_cast<void>(raspunsUtilizator); //pt advertisment git
        return false;
    }

    [[nodiscard]]virtual bool verificaRaspunsText(const std::string &raspunsUtilizator) const = 0;

    [[nodiscard]]virtual int calculeazaPunctaj() ///functie virtuala
    const = 0;

    ///permite copierea obiectelor derivate
    [[nodiscard]]virtual std::unique_ptr<Intrebare> clone() const = 0;

    virtual void afiseazaDetalii(std::ostream &os) const = 0;

    virtual void afiseazaTipIntrebare() const = 0;
    [[nodiscard]]const std::string& getText() const { return text; }

    /*static size_t getContorIntrebari() {
        return nrIntrebariTotale;
    }*/

    ///interfata non-virtuala
    // void afiseaza(std::ostream &os) const {
    //    //     os << "[INTREBARE]: " << text << "\n";
    //    //     afiseazaDetalii(os); ///apel polimorfic
    //    // }

    ///gettere comune
    /*const std::string& getText() const;
    int getraspunsCorectIndex() const;*/

    friend std::ostream &operator<<(std::ostream &os, const Intrebare &i);
};

#endif
