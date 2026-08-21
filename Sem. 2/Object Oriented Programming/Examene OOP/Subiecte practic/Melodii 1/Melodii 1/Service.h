#pragma once

#include "Repo.h"

class Service
{
	Repo& repo;
public:
	Service(Repo& repo) : repo{ repo } {}

	vector<Melodie> getSortRank() const;

	void modifica(int id, string titlu, int rank) {
		repo.modificaMelodie(id, titlu, rank);
	}

	void sterge(int id);
};

