#pragma once

#include <string>
using std::string;

class Melodie
{
	int id;
	string titlu;
	string artist;
	int rank;

public:

	Melodie(int id, string titlu, string artist, int rank) 
		: id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {}

	int getId() const { return id; }
	string getTitlu() const { return titlu; }
	string getArtist() const { return artist; }
	int getRank() const { return rank; }

	void setTitlu(string titluNou) { titlu = titluNou; }
	void setRank(int rankNou) { rank = rankNou; }
};

