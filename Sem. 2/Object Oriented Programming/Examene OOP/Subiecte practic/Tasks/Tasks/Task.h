#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

class Task
{
	int id;
	string descriere;
	vector<string> programatori;
	string stare;
public:
	Task(int id, const string& descriere, const vector<string>& programatori, const string& stare)
		: id{ id }, descriere{ descriere }, programatori{ programatori }, stare{ stare } {}

	int getId() const { return id; }
	string getDescriere() const { return descriere; }
	vector<string> getProgramatori() const { return programatori; }
	string getStare() const { return stare; }

	void setStare(const string& newStare) {
		stare = newStare;
	}
};

