#pragma once

#include <functional>
using std::function;

#include "Repo.h"
#include "Validator.h"

class Service
{
private:
	Repo rep;
	Validator val;

	/*
	* Sorteaza cartile dupa un criteriu dat
	* @param cmp: functia de comparare pentru sortare
	* pre: cmp este o functie de comparare valida
	* post: service nu se modifica
	* @return: o lista cu indicii cartilor sortate dupa criteriul dat
	*/
	Lista<int> generalSort(const function<bool(const Carte&, const Carte&)>& cmp) const;

	/*
	* Filtreaza cartile dupa un criteriu dat
	* @param fct: functia de filtrare
	* pre: fct este o functie de filtrare valida
	* post: service nu se modifica
	* @return: o lista cu indicii cartilor care indeplinesc criteriul de filtrare
	*/
	Lista<int> generalFilter(const function<bool(const Carte&)>& fct) const;

public:

	/*
	* Adauga o carte, daca este valida
	* @param id, titlu, autor, gen, an: campurile cartii
	* pre: -
	* post: se adauga cartea daca este valida
	* @throws ValidationError daca datele nu sunt valide
	* @throws RepoError daca mai exista o carte cu acelasi id
	*/
	void addCarte(int id, const string& titlu, const string& autor, const string& gen, int an);

	/*
	* Sterge o carte, daca exista
	* @param id: id-ul cartii de sters
	* pre: -
	* post: se sterge cartea, daca exista
	* @throws RepoError daca nu exista carte cu acest id
	*/
	void deleteCarte(int id);

	/*
	* Modifica o carte, daca este valida si exista
	* @param id, titlu, autor, gen, an: campurile cartii
	* pre: -
	* post: se modifica cartea daca exista si modificarea este valida
	* @throws ValidationError daca datele nu sunt valide
	* @throws RepoError daca nu exista carte cu acest id
	*/
	void updateCarte(int id, const string& titlu, const string& autor, const string& gen, int an);

	/*
	* Cauta cartea cu un id dat
	* @param id: id-ul cartii pe care o cautam
	* pre: exista cartea cu id dat
	* post: repo nu se modifica
	* @return: referinta const la cartea gasita
	* @throws RepoError daca nu exista carte cu acest id
	*/
	const Carte& findCarte(int id) const;

	/*
	* Returneaza toate cartile stocate
	* pre: -
	* post: repo nu se modifica
	* @return: lista tuturor cartilor
	*/
	const Lista<Carte>& getAll() const;

	/*
	* Sorteaza cartile dupa titlu
	* pre: -
	* post: service nu se modifica
	* @return: o lista cu indicii cartilor sortate dupa titlu
	*/
	Lista<int> sortByTitlu() const;

	/*
	* Sorteaza cartile dupa autor
	* pre: -
	* post: service nu se modifica
	* @return: o lista cu indicii cartilor sortate dupa autor
	*/
	Lista<int> sortByAutor() const;

	/*
	* Sorteaza cartile dupa an + gen
	* pre: -
	* post: service nu se modifica
	* @return: o lista cu indicii cartilor sortate dupa an + gen
	*/
	Lista<int> sortByAnGen() const;

	/*
	* Filtreaza cartile dupa titlu
	* @param titlu: titlul dupa care se filtreaza
	* pre: -
	* post: service nu se modifica
	* @return: o lista cu indicii cartilor filtrate dupa titlu
	*/
	Lista<int> filterByTitlu(const string& titlu) const;

	/*
	* Filtreaza cartile dupa an
	* @param an: anul dupa care se filtreaza
	* pre: -
	* post: service nu se modifica
	* @return: o lista cu indicii cartilor filtrate dupa an
	*/
	Lista<int> filterByAn(int an) const;
};