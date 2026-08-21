#pragma once
#include "Repo.h"
#include "Validator.h"

#include <map>
using std::map;

class Service
{
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) : repo{ repo }, val{ val } {}

	vector<Produs> getSortatPret();
	void adauga(int id, string nume, string tip, double pret);

	map<string, int> getRaportTip() const;
};

