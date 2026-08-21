#pragma once

#include <string>
using std::string;

class Carte
{
private:
	int id;
	string titlu;
	string autor;
	int pret;
public:

	Carte(int id, const string& titlu, const string& autor, int pret) : id{ id }, titlu{ titlu }, autor{ autor }, pret{ pret } {};
	~Carte() {};

	const int getId() const {
		return id;
	}
	const string getTitlu() const {
		return titlu;
	}
	const string getAutor() const {
		return autor;
	}
	const int getPret() const {
		return pret;
	}

	void setPret(int pretNou) {
		pret = pretNou;
	}
};

