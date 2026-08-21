#pragma once

#include <functional>
#include <memory>
#include <vector>
using std::function;
using std::unique_ptr;
using std::vector;

#include "ActiuneUndo.h"
#include "Repo.h"
#include "Validator.h"
#include "CosCarti.h"
#include "DTORaport.h"

class Service
{
private:
	Repo defaultRepo;
	RepoAbstract& rep;
	Validator val;

	CosCarti cos;

	vector<unique_ptr<ActiuneUndo>> undoActions;

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
	Service();

	explicit Service(RepoAbstract& rep);

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
	* Reface ultima operatie de adaugare/stergere/modificare.
	* pre: exista cel putin o operatie care poate fi refacuta
	* post: ultima operatie este anulata
	* @throws RepoError daca nu exista operatii de undo
	*/
	void undo();

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

	/*
	* Adauga o carte in cos
	* @param titlu: titlul cartii de adaugat
	* pre: -
	* post: cartea este adaugata in cos
	* @throws RepoError daca nu exista carte cu acest titlu
	*/
	void adaugaCos(const string& titlu);

	/*
	* Goleste cosul de carti
	* pre: -
	* post: cosul este gol
	*/
	void golesteCos() noexcept;

	/*
	* Genereaza un cos cu un numar dat de carti random
	* @param nr: numarul de carti din cos
	* pre: nr este un numar pozitiv
	* post: cosul este generat cu nr carti random
	*/
	void genereazaCos(int nr);

	/*
	* Sterge din cos o carte cu id dat
	* @param id: id-ul cartii de sters din cos
	*/
	void stergeCos(int id);

	/*
	* Returneaza cartile din cos
	* pre: -
	* post: cosul nu se modifica
	* @return: lista cu indicii cartilor din cos
	*/
	const Lista<int>& getCos() const noexcept;

	/*
	* Returneaza obiectul de tip cos asociat service-ului
	*/
	CosCarti& getCosCarti() noexcept;

	/*
	* Returneaza numarul de carti din cos
	* pre: -
	* post: cosul nu se modifica
	* @return: numarul de carti din cos
	*/
	int sizeCos() const noexcept;

	/*
	* Exporta cartile din cos intr-un fisier CSV
	* @param numeFisier: numele fisierului de exportat
	* pre: numeFisier este un string valid pentru un nume de fisier
	* post: cartile din cos sunt exportate in fisierul numeFisier in format CSV
	*/
	void exportCosCSV(const string& numeFisier) const;

	/*
	* Genereaza un raport cu numarul de carti pentru fiecare gen
	* pre: -
	* post: service nu se modifica
	* @return: o lista de DTO-uri cu genul si numarul de carti pentru fiecare gen
	*/
	Lista<DTORaport> raportGen() const;

};
