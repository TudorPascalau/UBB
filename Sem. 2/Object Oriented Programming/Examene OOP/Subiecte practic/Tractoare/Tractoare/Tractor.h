#pragma once

#include <string>
using std::string;

class Tractor
{
	int id;
	string denumire;
	string tip;
	int nrRoti;

public:
	Tractor(int id, string denumire, string tip, int nrRoti) : id{ id }, denumire{ denumire }, tip{ tip }, nrRoti{ nrRoti } {}

	int getId() const { return id; }
	string getDenumire() const { return denumire; }
	string getTip() const { return tip; }
	int getNrRoti() const { return nrRoti; }

	void setNrRoti(int nr) { nrRoti = nr; }
};

