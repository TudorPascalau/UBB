#pragma once
#include "Repo.h"
#include "Validator.h"

#include <algorithm>

class Service
{
	Repo& repo;
	Validator& val;
public:
	Service(Repo& repo, Validator& val) : repo{ repo }, val{ val } {}

	vector<Task> getSortatStare() const;
	vector<Task> filterNume(const string& nume) const;

	void adauga(int id, const string& descriere, const vector<string>& programatori, const string& stare);

	void modifica(int id, const string& newStare) {
		repo.modificaStare(id, newStare);
	}
};

