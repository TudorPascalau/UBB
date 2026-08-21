#pragma once

#include <string>
using std::string;

class Melodie
{
	int id;
	string titlu;
	string artist;
	string gen;

public:
	Melodie(int id, string titlu, string artist, string gen)
		: id{ id }, titlu{ titlu }, artist{ artist }, gen{ gen } {}

	int getId() const { return id; }
	string getTitlu() const { return titlu; }
	string getArtist() const { return artist; }
	string getGen() const { return gen; }
};

