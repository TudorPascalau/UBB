#pragma once

#include <string>
using std::string;

class Rochie
{
private:
	int cod;
	string denumire;
	string marime;
	int pret;
	bool disponibil;

public:

	Rochie(int cod, string denumire, string marime, int pret, bool disponibil) 
		: cod{ cod }, denumire{ denumire }, marime{ marime }, pret{ pret }, disponibil{ disponibil } {};

	int getCod() const{
		return cod;
	}

	string getDenumire() const{
		return denumire;
	}

	string getMarime() const{
		return marime;
	}

	int getPret() const{
		return pret;
	}

	bool getDisponibil() const{
		return disponibil;
	}

	void setDisponibil(bool dispNoua) {
		disponibil = dispNoua;
	}
};

