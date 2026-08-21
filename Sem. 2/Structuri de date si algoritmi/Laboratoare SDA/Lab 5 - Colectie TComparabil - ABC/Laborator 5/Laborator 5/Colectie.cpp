#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

//Theta(1)
Nod::Nod(TElem e, Nod* st, Nod* dr) : elem{ e }, st{ st }, dr{ dr } { 
	frecventa = 1; 
}

//Theta(1)
bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

//Theta(1)
Colectie::Colectie() {
	rad = nullptr;
	nrElem = 0;
}

//O(h), unde h este inaltimea ABC
void Colectie::distrug_rec(Nod* p) {
	if (p != nullptr) {
		distrug_rec(p->st);
		distrug_rec(p->dr);
		delete p;
	}
}

//O(h), unde h este inaltimea ABC
void Colectie::adauga(TElem e) {
	if (rad == nullptr) {
		rad = new Nod(e, nullptr, nullptr);
		nrElem++;
		return;
	}

	else {
		Nod* p = rad;
		Nod* parinte = nullptr;

		while (p != nullptr) {
			parinte = p;

			if (p->elem == e) {
				p->frecventa++;
				nrElem++;
				return;
			}

			else if (rel(e, p->elem))
				p = p->st;
			else
				p = p->dr;
		}

		Nod* nou = new Nod(e, nullptr, nullptr);
		if (rel(e, parinte->elem))
			parinte->st = nou;
		else parinte->dr = nou;

		nrElem++;
	}
}

//O(h), unde h este inaltimea ABC
bool Colectie::sterge(TElem e) {
	Nod* p = rad;
	Nod* parinte = nullptr;

	while (p != nullptr && p->elem != e) {
		parinte = p;
		if (rel(e, p->elem))
			p = p->st;
		else 
			p = p->dr;
	}

	if (p == nullptr) {
		return false;
	}

	if (p->frecventa > 1) {
		p->frecventa--;
	}

	else if (p->st == nullptr || p->dr == nullptr) {
		Nod* copil = nullptr;
		if (p->st != nullptr) 
			copil = p->st;
		else
			copil = p->dr;

		if (parinte == nullptr) 
			rad = copil;
		else if (parinte->st == p)
			parinte->st = copil;
		else 
			parinte->dr = copil;

		delete p;
	}

	else {
		Nod* parinteSucc = p;
		Nod* succ = p->dr;

		while (succ->st != nullptr) {
			parinteSucc = succ;
			succ = succ->st;
		}

		p->elem = succ->elem;
		p->frecventa = succ->frecventa;

		Nod* copilSucc = succ->dr;
		if (parinteSucc->st == succ)
			parinteSucc->st = copilSucc;
		else
			parinteSucc->dr = copilSucc;

		delete succ;
		
	}

	nrElem--;
	return true;
}

//O(h), unde h este inaltimea ABC
bool Colectie::cauta(TElem elem) const {
	Nod* p = rad;

	while (p != nullptr) {
		if (p->elem == elem) {
			return true;
		}

		if (rel(elem, p->elem)) {
			p = p->st;
		}
		else {
			p = p->dr;
		}
	}

	return false;
}

//O(h), unde h este inaltimea ABC
int Colectie::nrAparitii(TElem elem) const {
	Nod* p = rad;

	while (p != nullptr) {
		if (p->elem == elem) {
			return p->frecventa;
		}

		if (rel(elem, p->elem)) {
			p = p->st;
		}
		else {
			p = p->dr;
		}
	}

	return 0;
}

//Theta(1)
int Colectie::dim() const {
	return nrElem;
}

//Theta(1)
bool Colectie::vida() const {
	return (nrElem == 0);
}

//O(h) unde h este inaltimea arborelui
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//Theta(m), unde m este numarul de elemente
Colectie::~Colectie() {
	distrug_rec(rad);
}
