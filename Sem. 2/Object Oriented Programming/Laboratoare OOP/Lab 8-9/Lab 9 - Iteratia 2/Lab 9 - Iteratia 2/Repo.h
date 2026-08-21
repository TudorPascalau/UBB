#pragma once

#include "Lista.h"
#include "Carte.h"
#include "AbstractRepo.h"

class Repo : public RepoAbstract
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
	int findPozById(int id) const noexcept;

public:
	virtual ~Repo() = default;

	/*
	* Returneaza numarul de carti stocate
	* pre: -
	* post: repo nu se modifica
	* @return: numarul de carti stocate
	*/
	int repoSize() const noexcept override;


	/*
	* Adauga o carte in repository
	* @param c: cartea de adaugat
	* pre: c este valida
	* post: daca nu exista deja o carte cu acelasi id, se adauga
	* @throws RepoError daca mai exista o carte cu acelasi id
	*/
	void addCarte(const Carte& c) override;

	/*
	* Sterge o carte dupa id
	* @param id: id-ul cartii de sters
	* pre: -
	* post: daca exista o carte cu id-ul dat, aceasta este stearsa
	* @throws RepoError daca nu exista carte cu id-ul dat
	*/
	void deleteCarte(int id) override;

	/*
	* Modifica o carte identificata dupa id
	* @param c: noua carte
	* pre: c este valida
	* post: daca exista o carte cu acelasi id, campurile ei sunt actualizate
	* @throws RepoError daca nu exista carte cu acelasi id
	*/
	void updateCarte(const Carte& c) override;

	/*
	* Cauta cartea cu un id dat
	* @param id: id-ul cartii pe care o cautam
	* pre: exista cartea cu id dat
	* post: repo nu se modifica
	* @return: referinta const la cartea gasita
	* @throws RepoError daca nu exista carte cu id-ul dat
	*/
	const Carte& getById(int id) const override;

	/*
	* Returneaza toate cartile din repository
	* pre: -
	* post: repo nu se modifica
	* @return: lista tuturor cartilor
	*/
	const Lista<Carte>& getAll() const noexcept override;

};

