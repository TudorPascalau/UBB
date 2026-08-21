#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <exception>
#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class DO {
	friend class Iterator;
    private:
		
		int m;
		int n;
		TElem* e;
		int* urm;
		int primLiber;
		Relatie rel;

		bool* ocupat;

		// functia de dispersie
		int d(TCheie c) const;

		// actualizeaza primLiber
		void actPrimLiber();

		// redimensioneaza tabela
		void redim();

    public:

	// constructorul implicit al dictionarului
	DO(Relatie r);


	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	//verifica daca dictionarul e vid
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;

	// returneaza valoarea care apare cel mai frecvent in dictionar. Daca mai multe valori apar cel mai frecvent, se returneaza una (oricare)
	// Daca dictionarul este vid, operatia returneaza NULL_TVALOARE
	TValoare ceaMaiFrecventaValoare() const;

	// destructorul dictionarului
	~DO();


};
