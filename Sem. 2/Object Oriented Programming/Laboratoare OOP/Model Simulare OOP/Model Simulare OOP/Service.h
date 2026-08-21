#pragma once

#include "Repo.h"

class Service
{
private:

	Repo& repo;

public:
    Service(Repo& repo) : repo(repo) {}
	~Service() {}

	const vector<Rochie>& getAllNesortat() const{
		return repo.getAll();
	}

	void inchireaza(int cod) {
		repo.inchireazaRochie(cod);
	}

	vector<Rochie> sortPret() const;
	vector<Rochie> sortMarime() const;
};

