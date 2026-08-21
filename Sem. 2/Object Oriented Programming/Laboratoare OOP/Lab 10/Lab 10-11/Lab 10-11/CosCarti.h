#pragma once

#include "Lista.h"
#include "Carte.h"
#include "Observer.h"

class CosCarti : public Observable {
private:
	Lista<int> idCarti;

public:

	/*
	* Adauga o carte in cos
	* @param c: cartea de adaugat
	* pre: -
	* post: cartea este adaugata in cos
	*/
	void adauga(int id);

	/*
	* Goleste cosul de carti
	* pre: -
	* post: cosul este gol
	*/
	void goleste() noexcept;

	/*
	* Sterge o carte din cos, daca exista
	* @param id: id-ul cartii de sters
	* pre: -
	* post: se sterge cartea din cos, daca exista
	*/
	void stergeId(int id);

	/*
	* Returneaza toate id-urile cartilor din cos
	* pre: -
	* post: cosul nu se modifica
	* @return: o lista cu id-urile cartilor din cos
	*/
	const Lista<int>& getAll() const noexcept;

	/*
	* Returneaza numarul de carti din cos
	* pre: -
	* post: cosul nu se modifica
	* @return: numarul de carti din cos
	*/
	int size() const noexcept;
};