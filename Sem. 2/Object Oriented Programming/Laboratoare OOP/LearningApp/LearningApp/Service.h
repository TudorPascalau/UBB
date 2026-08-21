#pragma once

#include "Repo.h"

class Service
{
private:
	Repo repo;
public:
	Service(Repo repo) : repo{ repo } {}
	~Service() = default;

	void adaugaCarte(int id, const string& titlu, string& autor, int pret) {
		Carte c(id, titlu, autor, pret);
		repo.adauga(c);
	}
	vector<Carte> getAllCarti() const {
		return repo.getAll();
	}
};

