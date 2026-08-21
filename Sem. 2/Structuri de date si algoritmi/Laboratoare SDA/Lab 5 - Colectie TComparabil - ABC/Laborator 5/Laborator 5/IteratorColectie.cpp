#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>
using std::exception;

//Theta(1)
void IteratorColectie::push(Nod* p) {
	stiva[++top] = p;
}

//Theta(1)
Nod* IteratorColectie::pop() {
	return stiva[top--];
}

//Theta(1)
Nod* IteratorColectie::varf() const {
	return stiva[top];
}

//Theta(1)
bool IteratorColectie::stivaVida() const {
	return top == -1;
}

//O(h), h depinde de inaltimea la care se alfa nodul p
void IteratorColectie::adaugaRamuraStanga(Nod* p) {
	while (p != nullptr) {
		push(p);
		p = p->st;
	}
}

//O(h), unde h este inaltimea ABC
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	capacitate = col.dim();

	if (capacitate == 0) capacitate = 1;

	stiva = new Nod*[capacitate];
	top = -1;
	curent = nullptr;
	aparitieCurenta = 0;

	prim();
}

//Theta(1)
IteratorColectie::~IteratorColectie() {
	delete[] stiva;
}

//Theta(1)
TElem IteratorColectie::element() const{
	if (!valid()) {
		throw exception();
	}

	return curent->elem;
}

//Theta(1)
bool IteratorColectie::valid() const {
	return (curent != nullptr);
}

//O(h) defavorabil, Theta(1) amortizat
void IteratorColectie::urmator() {
	if (!valid()) {
		throw exception();
	}

	if (aparitieCurenta < curent->frecventa) {
		aparitieCurenta++;
		return;
	}
	else {
		Nod* p = pop();
		if (p->dr != nullptr) {
			adaugaRamuraStanga(p->dr);
		}

		if (!stivaVida()) {
			curent = varf();
			aparitieCurenta = 1;
		}
		else {
			curent = nullptr;
			aparitieCurenta = 0;
		}
	}
}

//O(h), unde h este inaltimea ABC
void IteratorColectie::prim() {
	top = -1;
	adaugaRamuraStanga(col.rad);

	if (!stivaVida()) {
		curent = varf();
		aparitieCurenta = 1;
	}
	else {
		curent = nullptr;
		aparitieCurenta = 0;
	}
}
