#pragma once

#include <string>
using std::string;

class Articol
{
private:
    int cod;
    string categorie;
    string brand;
    string marime;
public:

    /*
    * Constructor pentru articol
    */
    Articol(int cod, const string& brand, const string& categorie, const string& marime)
        : cod(cod), categorie(categorie), brand(brand), marime(marime) {};

    
    /*
    * Getter pentru cod
    * @returns: codul unui articol
    */
    int getCod() const {
        return cod;
    }

    /*
    * Getter pentru categorie
    * @returns: categoria unui articol
    */
    string getCategorie() const {
        return categorie;
    }

    /*
    * Getter pentru brand
    * @returns: brandul unui articol
    */
    string getBrand() const {
        return brand;
    }

    /*
    * Getter pentru marime
    * @returns: marimea unui articol
    */
    string getMarime() const {
        return marime;
    }
};

