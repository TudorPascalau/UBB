
#include "Coada.h"
#include <exception>
#include <iostream>

using namespace std;

/*
* Complexitate timp Theta(1)
* Folosim pozitiile 1..cap
*/
Coada::Coada() {
	cap = 2;
	elems = new TElem[cap + 1];
	fata = 1; 
	spate = 1; 

}

/*
* Complexitate timp Theta(n)
*/
void Coada::redimensionare() {
	int capNoua = cap * 2;
	TElem* elemsNoi = new TElem[capNoua + 1];

	if (fata < spate) {
		for (int i = fata; i < spate; i++) {
			elemsNoi[i] = elems[i];
		}
	}

	// caz "depasire circulara"
	else if (fata > spate) {
		

		for (int i = 1; i < spate; i++) {
			elemsNoi[i] = elems[i];
		}

		int offset = capNoua - cap;

		for (int i = fata; i <= cap; i++) {
			elemsNoi[i + offset] = elems[i];
		}

		fata = fata + offset;

	}

	delete[] elems;

	elems = elemsNoi;
	cap = capNoua;
}


/*
* Complexitate timp amortizata Theta(1) 
* Complexitate caz defavorabil Theta(n)
*/ 
void Coada::adauga(TElem elem) {
	
	if ((fata == 1 && spate == cap) || // coada plina caz a)
		(fata == spate + 1)) { // coada plina caz b)
		redimensionare();
	}

	elems[spate] = elem;
	if (spate == cap) 
		spate = 1;
	else 
		spate = spate + 1;
}

/*
* Arunca exceptie daca coada e vida
* Complexitate timp Theta(1)
*/
TElem Coada::element() const {
	if (vida())
		throw exception();

	return elems[fata];
}

/*
* Arunca exceptie daca coada e vida
* Complexitate timp Theta(1)
*/
TElem Coada::sterge() {
	if (vida())
		throw exception();

	TElem e = elems[fata];

	if (fata == cap)
		fata = 1;
	else
		fata++;

	return e;
}

/*
* Complexitate timp Theta(1)
*/
bool Coada::vida() const {
	return fata == spate;
}

/*
* Complexitate timp Theta(1)
*/
Coada::~Coada() {
	delete[] elems;
}

