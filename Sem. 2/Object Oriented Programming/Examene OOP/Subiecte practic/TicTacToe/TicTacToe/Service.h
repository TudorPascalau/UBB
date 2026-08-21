#pragma once
#include "Repo.h"
#include "Validator.h"

class Service
{
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) : repo{ repo }, val{ val } {}

	vector<XO> getSortatStare() const;
	void adauga(int dim, string table, string player);
	void modifica(int id, int dim, string table, string player, string stare);

	XO getJocById(int id);
};

