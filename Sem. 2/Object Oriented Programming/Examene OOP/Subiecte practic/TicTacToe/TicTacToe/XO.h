#pragma once

#include <string>
using std::string;

class XO
{
	int id;
	int dim;
	string tabla;
	string player;
	string stare;
public:
	XO(int id, int dim, string tabla, string player, string stare)
		: id{ id }, dim{ dim }, tabla{ tabla }, player{ player }, stare{ stare } {}

	int getId() const { return id; }
	int getDim() const { return dim; }
	string getTabla() const { return tabla; }
	string getPlayer() const { return player; }
	string getStare() const { return stare; }

	void setDim(int dimNou) { dim = dimNou; }
	void setTabla(string tablaNou) { tabla = tablaNou; }
	void setPlayer(string playerNou) { player = playerNou; }
	void setStare(string stareNou) { stare = stareNou; }
};

