#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */

	TCheie* chei;
	int* urmChei;
	int* precChei;

	int primChei;
	int ultimChei;
	int primLiberChei;
	int cpChei;

	int* primVal;
	int* ultimVal;

	TValoare* valori;
	int* urmValori;
	int* precValori;

	int primLiberValori;
	int cpValori;

	int nrPerechi;

	int alocaChei();
	void dealocaChei(int i);

	int alocaValoare();
	void dealocaValoare(int i);

	void redimChei();
	void redimValori();

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// elimina o cheie impreuna cu toate valorile sale
	// returneaza un vector cu valorile care au fost anterior asoicate acestei chei (si au fost eliminate)
	vector<TValoare> stergeValoriPentruCheie(TCheie cheie);

	// destructorul MultiDictionarului	
	~MD();



};

