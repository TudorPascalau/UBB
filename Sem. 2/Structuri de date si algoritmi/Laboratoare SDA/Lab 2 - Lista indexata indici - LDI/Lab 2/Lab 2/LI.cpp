#include <exception>
#include <iostream>
#include "LI.h"
#include "IteratorLI.h"

// Theta(1)
Nod::Nod(TElem e, Nod* urm, Nod* prec) {
	this->e = e;
	this->urm = urm;
	this->prec = prec;
}

TElem Nod::element() {
	return e;
}

Nod* Nod::urmator() {
	return urm;
}

Nod* Nod::precedent() {
	return prec;
}

// Theta(1)
LI::LI() {
	this->prim = nullptr;
	this->ultim = nullptr;
	this->lungime = 0;
}

// Theta(1)
int LI::dim() const {
	return lungime;
}

// Theta(1)
bool LI::vida() const {
	return lungime == 0;
}

// Theta(i) / O(n)
TElem LI::element(int i) const {
	if(i < 0 || i > dim() - 1)
		throw std::exception();

	IteratorLI it = iterator();
	for (int poz = 0; poz < i; poz++)
		it.urmator();

	return it.element();
}

// Theta(i) / O(n)
TElem LI::modifica(int i, TElem e) {
	if (i < 0 || i > dim() - 1)
		throw std::exception();

	IteratorLI it = iterator();
	for (int poz = 0; poz < i; poz++)
		it.urmator();

	TElem vechi = it.element();
	it.curent->e = e;
	return vechi;
}

// Theta(1)
void LI::adaugaSfarsit(TElem e) {
	Nod* nou = new Nod(e, nullptr, ultim);

	// Daca lista e vida, noul nod devine primul si ultimul nod
	if (this->prim == nullptr) {
		prim = nou;
		ultim = nou;
	}

	// Daca lista nu e vida, legam ultimul nod cu noul nod si noul nod devine ultimul nod
	else
	{
		ultim->urm = nou;
		nou->prec = ultim;
		ultim = nou;
	}

	lungime++;
}

// Theta(i) / O(n)
void LI::adauga(int i, TElem e) {
	if (i < 0 || i > dim())
		throw std::exception();

	Nod* nou = new Nod(e, nullptr, nullptr);

	// Daca adaugam la sfarsit, trebuie tratate separat cazurile limita
	if (i == dim()) {
		adaugaSfarsit(e);
		return;
	}

	IteratorLI it = iterator();
	for (int poz = 0; poz < i; poz++)
		it.urmator();

	Nod* curent = it.curent;
	nou->prec = curent->prec;
	nou->urm = curent;

	// Daca adaugam pe prima pozitie, noul nod devine primul nod
	if(curent == prim)
		prim = nou;
	// Daca adaugam pe o pozitie din mijlocul listei, legam nodul precedent cu noul nod
	else
		curent->prec->urm = nou;

	curent->prec = nou;
	lungime++;
}

// Theta(i) / O(n)
TElem LI::sterge(int i) {
	if (i < 0 || i > dim() - 1)
		throw std::exception();

	IteratorLI it = iterator();
	for (int poz = 0; poz < i; poz++)
		it.urmator();

	Nod* curent = it.curent;
	TElem e = curent->element();

	// Daca avem un singur element in lista, se sterge toata lista
	if (prim == ultim) {
		prim = nullptr;
		ultim = nullptr;
	}

	// Daca stergem primul element, al doilea element devine primul element
	else if (curent == prim) {
		prim = curent->urm;
		prim->prec = nullptr;
	}

	// Daca stergem ultimul element, penultimul element devine ultimul element
	else if (curent == ultim) {
		ultim = curent->prec;
		ultim->urm = nullptr;
	}

	// Daca stergem un element din mijlocul listei, legam nodul precedent cu nodul urmator
	else {
		curent->prec->urm = curent->urm;
		curent->urm->prec = curent->prec;
	}

	delete curent;
	lungime--;

	return e;
}

// O(n)
int LI::cauta(TElem e) const{
	IteratorLI it = iterator();
	int i = 0;
	while (it.valid()) {
		if (it.element() == e)
			return i;
		i++;
		it.urmator();
	}

	return -1;
}

// Theta(1)
IteratorLI LI::iterator() const {
	return IteratorLI(*this);
}

// Theta(n)
LI::~LI() {
	IteratorLI it = iterator();
	while (it.valid()) {
		Nod* de_sters = it.curent;
		it.urmator();
		delete de_sters;
	}
}
