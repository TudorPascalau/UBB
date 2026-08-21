#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <unordered_map>

using namespace std;

// functia de dispersie
// Theta(1)
int DO::d(TCheie c) const {
	return abs(c) % m;
}

// actualizeaza primLiber
// O(m)
void DO::actPrimLiber() {
	primLiber++;

	while (primLiber < m && ocupat[primLiber]) {
		primLiber++;
	}
}

// redimensioneaza tabela de dispersie
// Theta(m)
void DO::redim() {
	int mVechi = m;
	TElem* eVechi = e;
	int* urmVechi = urm;
	bool* ocupatVechi = ocupat;

	m = m * 2;
	e = new TElem[m];
	urm = new int[m];
	ocupat = new bool[m];

	for (int i = 0; i < m; i++) {
		e[i] = TElem(NULL_TVALOARE, NULL_TVALOARE);
		urm[i] = -1;
		ocupat[i] = false;
	}

	primLiber = 0;
	int nVechi = n;
	n = 0;

	for (int i = 0; i < mVechi; i++) {
		if (ocupatVechi[i]) {
			adauga(eVechi[i].first, eVechi[i].second);
		}
	}

	n = nVechi;

	delete[] eVechi;
	delete[] urmVechi;
	delete[] ocupatVechi;
}

// Theta(m);
DO::DO(Relatie r) {
	m = 10;
	n = 0;
	rel = r;

	e = new TElem[m];
	urm = new int[m];
	ocupat = new bool[m];

	for (int i = 0; i < m; i++) {
		e[i] = TElem(NULL_TVALOARE, NULL_TVALOARE);
		urm[i] = -1;
		ocupat[i] = false;
	}

	primLiber = 0;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
//O(n) defavorabil, Theta(1) in medie in ipoteza dispersiei uniforme
TValoare DO::adauga(TCheie c, TValoare v) {

	if (primLiber >= m) {
		redim();
	}

	int i = d(c);

	if (!ocupat[i]) {
		e[i] = TElem(c, v);
		urm[i] = -1;
		ocupat[i] = true;
		n++;

		if (i == primLiber) {
			actPrimLiber();
		}

		return NULL_TVALOARE;
	}

	int j = -1;
	while (i != -1) {
		if (e[i].first == c) {
			TValoare valVeche = e[i].second;
			e[i].second = v;
			return valVeche;
		}
		j = i;
		i = urm[i];
	}

	e[primLiber] = TElem(c, v);
	urm[primLiber] = -1;
	ocupat[primLiber] = true;
	urm[j] = primLiber;

	n++;
	actPrimLiber();

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
//O(n) defavorabil, Theta(1) in medie in ipoteza dispersiei uniforme
TValoare DO::cauta(TCheie c) const {
	int i = d(c);

	while (i != -1) {
		if(e[i].first == c) {
			return e[i].second;
		}
		i = urm[i];
	}

	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
//O(n) defavorabil, Theta(1) in medie in ipoteza dispersiei uniforme
TValoare DO::sterge(TCheie c) {
	int poz = d(c);
	int anterior = -1;

	while (poz != -1 && e[poz].first != c) {
		anterior = poz;
		poz = urm[poz];
	}

	if (poz == -1) {
		return NULL_TVALOARE;
	}

	TValoare valSterge = e[poz].second;
	ocupat[poz] = false;
	bool gata = false;
	while (!gata) {
		int p = poz;
		int q = urm[poz];

		while (q != -1 && d(e[q].first) != poz) {
			p = q;
			q = urm[q];
		}	

		if (q == -1) {
			if (anterior != -1) {
				urm[anterior] = urm[poz];
			}

			e[poz] = TElem(NULL_TVALOARE, NULL_TVALOARE);
			urm[poz] = -1;

			if (poz < primLiber) {
				primLiber = poz;
			}

			n--;
			gata = true;
		}

		else {
			e[poz] = e[q];
			anterior = p;
			poz = q;
		}
	}

	return valSterge;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
//Theta(1)
int DO::dim() const {
	return n;
}

//verifica daca dictionarul e vid
//Theta(1)
bool DO::vid() const {
	return n == 0;
}

//se returneaza iterator pe dictionar
//Theta(m)
Iterator DO::iterator() const {
	return  Iterator(*this);
}


// returneaza valoarea care apare cel mai frecvent in dictionar. Daca mai multe valori apar cel mai frecvent, se returneaza una (oricare)
// Daca dictionarul este vid, operatia returneaza NULL_TVALOARE
TValoare DO::ceaMaiFrecventaValoare() const {
	if (vid()) {
		return NULL_TVALOARE;
	}

	Iterator it = iterator();
	std::unordered_map<TValoare, int> frecventa;
	while(it.valid()) {
		TElem elem = it.element();
		TValoare val = elem.second;
		frecventa[val]++;
		it.urmator();
	}

	TValoare valFrecMax = NULL_TVALOARE;
	int frecMax = 0;
	for (const auto& pereche : frecventa) {
		if (pereche.second > frecMax) {
			frecMax = pereche.second;
			valFrecMax = pereche.first;
		}
	}

	return valFrecMax;
}

//destructorul dictionarului
//Theta(1)
DO::~DO() {
	delete[] e;
	delete[] urm;
	delete[] ocupat;
}
