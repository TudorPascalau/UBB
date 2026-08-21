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

	/*
	* Constructor pentru Task
	* @param id: id, descriere: descrieere, programatori: lista nume, stare: starea(open, closed, inprogress)
	*/
	Task(int id, const string& descriere, const vector<string>& programatori, const string& stare)
		: id{ id }, descriere{ descriere }, programatori{ programatori }, stare{ stare } {
	}

	/*
	* Getter pentru id-ul unui Task
	* @return id : int
	*/
	int getId() const { 
		return id; 
	}

	/*
	* Getter pentru descrierea unui Task
	* @return descriere: string
	*/
	string getDescriere() const { return descriere; }

	/*
	* Getter pentru lista de nume a programatorilor unui Task
	* @return programatori: lista string
	*/
	vector<string> getProgramatori() const { return programatori; }

	/*
	* Getter pentru starea unui Task
	* @return stare: string
	*/
	string getStare() const { return stare; }

	/*
	* Setter pentru starea unui Task
	* @param newStare: starea noua de setat
	* Post: se actualizeaza starea Task-ului
	*/
	void setStare(const string& newStare) {
		stare = newStare;
	}
};

