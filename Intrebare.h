#ifndef INTREBARE_H
#define INTREBARE_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

///clasa de baza
class Intrebare {
private:
    std::string text;
    static size_t nr_intrebari_totale;

protected: /// protected pentru a fi accesibile claselor derivate
    int raspunsCorect;

public:
    ///constructor de baza
    Intrebare(const std::string& t, int rC);

    ///constructor default
    Intrebare() : raspunsCorect{-1} {}
    virtual ~Intrebare();

    virtual bool verificaRaspuns(int raspuns_utilizator) const {
        return false;
    }
    virtual bool verificaRaspunsText(const std::string& raspuns_utilizator) const = 0;
    virtual int calculeazaPunctaj()
        const = 0;
    ///permite copierea obiectelor derivate
    virtual std::unique_ptr<Intrebare> clone() const = 0;
    virtual void afiseazaDetalii(std::ostream& os) const = 0;

    static size_t getContorIntrebari() {
        return nr_intrebari_totale;
    }

    ///interfata non-virtuala
    void afiseaza(std::ostream& os) const {
        os << "[INTREBARE]: " << text << "\n";
        afiseazaDetalii(os); ///apel polimorfic
    }

    ///gettere comune
    const std::string& getText() const;
    int getraspunsCorectIndex() const;

    friend std::ostream& operator<<(std::ostream& os, const Intrebare& intrebare) {
        intrebare.afiseaza(os);
        return os;
    }
};

#endif
