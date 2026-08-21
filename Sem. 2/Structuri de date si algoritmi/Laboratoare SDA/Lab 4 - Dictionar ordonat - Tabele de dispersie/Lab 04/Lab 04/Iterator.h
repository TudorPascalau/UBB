#pragma once

#include "DO.h"

class Iterator{
	friend class DO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const DO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;

	int curent;

	//returneaza pozitia primului element din container sau -1 daca containerul e vid
	int CautaPrim() const;

	//returneaza pozitia urmatorului element din container dupa pozitia poz sau -1 daca poz e ultima pozitie sau containerul e vid
	int CautaUrmator(int poz) const;


public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};

