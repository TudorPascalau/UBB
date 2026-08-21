#pragma once

#include "Repo.h"

class Service
{
	Repo& repo;
public:
	Service(Repo& repo) : repo{ repo } {}
	
	vector<Melodie> getSortateArtist();
	void adauga(string titlu, string artist, string gen);
	void sterge(int id) {
		repo.stergeRepo(id);
	}
};

