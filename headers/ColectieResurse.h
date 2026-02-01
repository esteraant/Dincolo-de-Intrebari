#ifndef COLECTIERESURSE_H
#define COLECTIERESURSE_H

#include <vector>

template <typename T>
class ColectieResurse {
private:
    std::vector<T> elemente;
public:
    void adauga(T element) {
        elemente.push_back(std::move(element));
    }

    size_t getDimensiune() const {
        return elemente.size();
    }

    // Returneaza elementul de la un anumit index
    const T& operator[](size_t index) const {
        return elemente[index];
    }
    
    const std::vector<T>& getToate() const { return elemente; }

};

#endif