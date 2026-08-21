#pragma once

#include "Repo.h"
#include "Validator.h"

class Service
{
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) : repo{ repo }, val{ val } {}

	vector<Tractor> getSortatDenumire() const;
	int nrTractoare() const {
		return repo.getAll().size();
	}

	void addTractor(int id, string denumire, string tip, int nrRoti);

	vector<string> getTipuri() const;

	void decrementRoti(int id);
};

