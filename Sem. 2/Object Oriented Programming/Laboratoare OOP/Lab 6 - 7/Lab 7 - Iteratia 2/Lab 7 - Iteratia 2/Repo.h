#pragma once

#include "Lista.h"
#include "Carte.h"

class RepoError {
private:
	string message;

public:
	/*
	* Constructor pentru clasa RepoError
	* @param message: mesajul de eroare
	* pre: -
	* post: este creat un obiect de tip RepoError
	*/
	explicit RepoError(const string& message) : message{ message } {
	}

	/*
	* Returneaza mesajul de eroare
	* pre: -
	* post: repoError nu se modifica
	* @return: mesajul de eroare
	*/
	const string& getMessage() const {
		return message;
	}
};

class Repo
{
private:
	Lista<Carte> repo;

	/*
	* Cauta pozitia unei carti dupa id
	* @param id: id-ul cartii
	* pre: -
	* post: repo nu se modifica
	* @return: pozitia cartii, daca exista;
	*		   -1, altfel
	*/
	int findPozById(int id) const;

public:

	/*
	* Returneaza numarul de carti stocate
	* pre: -
	* post: repo nu se modifica
	* @return: numarul de carti stocate
	*/
	int repoSize() const;


	/*
	* Adauga o carte in repository
	* @param c: cartea de adaugat
	* pre: c este valida
	* post: daca nu exista deja o carte cu acelasi id, se adauga
	* @throws RepoError daca mai exista o carte cu acelasi id
	*/
	void addCarte(const Carte& c);

	/*
	* Sterge o carte dupa id
	* @param id: id-ul cartii de sters
	* pre: -
	* post: daca exista o carte cu id-ul dat, aceasta este stearsa
	* @throws RepoError daca nu exista carte cu id-ul dat
	*/
	void deleteCarte(int id);

	/*
	* Modifica o carte identificata dupa id
	* @param c: noua carte
	* pre: c este valida
	* post: daca exista o carte cu acelasi id, campurile ei sunt actualizate
	* @throws RepoError daca nu exista carte cu acelasi id
	*/
	void updateCarte(const Carte& c);

	/*
	* Cauta cartea cu un id dat
	* @param id: id-ul cartii pe care o cautam
	* pre: exista cartea cu id dat
	* post: repo nu se modifica
	* @return: referinta const la cartea gasita
	* @throws RepoError daca nu exista carte cu id-ul dat
	*/
	const Carte& getById(int id) const;

	/*
	* Returneaza toate cartile din repository
	* pre: -
	* post: repo nu se modifica
	* @return: lista tuturor cartilor
	*/
	const Lista<Carte>& getAll() const;

};

