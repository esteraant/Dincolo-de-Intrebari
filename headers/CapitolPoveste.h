#ifndef CAPITOLPOVESTE_H
#define CAPITOLPOVESTE_H

/**
 *  @brief Represents a story chapter that can be unlocked during the game.
 * This class stores the narrative content and manages its visibility state.
 * Chapters are unlocked after completing a level.
 */

#include <iostream>
#include <string>

class CapitolPoveste {
private:
    std::string titlu;
    std::string continut;
    bool deblocat;

public:
    CapitolPoveste(const std::string &titlu, const std::string &continut) : deblocat{false} ///construtor de init
    {
        this->titlu = titlu;
        this->continut = continut;
    }

    CapitolPoveste() : deblocat{false} {
    } ///constructor default
    ~CapitolPoveste() = default; ///destructor

    void deblocheaza() {
        this->deblocat = true;
    }

    /*bool esteDeblocat() const { ///getter pt statusul deblocat
        return deblocat;
    }*/

    /*const std::string& getTitlu() const { ///getter pt titlu
        return titlu;
    }*/

    ///operator<<
    friend std::ostream &operator<<(std::ostream &os, const CapitolPoveste &cap) {
        os << "~     " << cap.titlu << "     ~\n";
        if (cap.deblocat) {
            os << cap.continut << "\n";
        } else {
            os << "Capitol blocat. Raspunde corect la intrebari pentru a-l debloca.\n";
        }
        return os;
    }
    bool esteFinalizat() const { return deblocat; }
    const std::string& getTitlu() const { return titlu; }
    const std::string& getText() const { return continut; }
};

#endif
