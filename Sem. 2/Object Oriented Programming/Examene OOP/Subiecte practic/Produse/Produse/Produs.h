#pragma once

#include <string>
using std::string;

class Produs
{
	int id;
	string nume;
	string tip;
	double pret;
public:
	Produs(int id, string nume, string tip, double pret)
		: id{ id }, nume{ nume }, tip{ tip }, pret{ pret } {}

	int getId() const { return id; }
	string getNume() const { return nume; }
	string getTip() const { return tip; }
	double getPret() const { return pret; }
};

