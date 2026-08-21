#pragma once

#include <string>
using std::string;

#include "Carte.h"
#include "Lista.h"

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
	const string& getMessage() const noexcept {
		return message;
	}
};

class RepoAbstract
{
public:
	virtual ~RepoAbstract() = default;

	/*
	* Returneaza numarul de carti stocate
	* pre: -
	* post: repo nu se modifica
	* @return: numarul de carti stocate
	*/
	virtual int repoSize() const = 0;

	/*
	* Adauga o carte in repository
	* @param c: cartea de adaugat
	* pre: c este valida
	* post: daca nu exista deja o carte cu acelasi id, se adauga
	* @throws RepoError daca mai exista o carte cu acelasi id
	*/
	virtual void addCarte(const Carte& c) = 0;

	/*
	* Sterge o carte dupa id
	* @param id: id-ul cartii de sters
	* pre: -
	* post: daca exista o carte cu id-ul dat, aceasta este stearsa
	* @throws RepoError daca nu exista carte cu id-ul dat
	*/
	virtual void deleteCarte(int id) = 0;

	/*
	* Modifica o carte identificata dupa id
	* @param c: noua carte
	* pre: c este valida
	* post: daca exista o carte cu acelasi id, campurile ei sunt actualizate
	* @throws RepoError daca nu exista carte cu acelasi id
	*/
	virtual void updateCarte(const Carte& c) = 0;

	/*
	* Cauta cartea cu un id dat
	* @param id: id-ul cartii pe care o cautam
	* pre: exista cartea cu id dat
	* post: repo nu se modifica
	* @return: referinta const la cartea gasita
	* @throws RepoError daca nu exista carte cu id-ul dat
	*/
	virtual const Carte& getById(int id) const = 0;

	/*
	* Returneaza toate cartile din repository
	* pre: -
	* post: repo nu se modifica
	* @return: lista tuturor cartilor
	*/
	virtual const Lista<Carte>& getAll() const = 0;
};

using AbstractRepo = RepoAbstract;
