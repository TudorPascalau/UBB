#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;

// Theta(1)
int MD::alocaChei() {
	
	if(primLiberChei == -1)
		redimChei();
	int i = primLiberChei;
	primLiberChei = urmChei[primLiberChei];
	return i;
}

// Theta(1)
void MD::dealocaChei(int i) {
	urmChei[i] = primLiberChei;
	precChei[i] = -1;

	primVal[i] = -1;
	ultimVal[i] = -1;

	primLiberChei = i;
}

// Theta(1)
int MD::alocaValoare() {
	if(primLiberValori == -1)
		redimValori();

	int i = primLiberValori;
	primLiberValori = urmValori[primLiberValori];
	return i;
}

// Theta(1)
void MD::dealocaValoare(int i) {
	urmValori[i] = primLiberValori;
	precValori[i] = -1;

	primLiberValori = i;
}

// Theta(cpChei)
void MD::redimChei() {
	int cpNou = cpChei * 2;

	TCheie* cheiNoi = new TCheie[cpNou];
	int* urmCheiNoi = new int[cpNou];
	int* precCheiNoi = new int[cpNou];
	int* primValNoi = new int[cpNou];
	int* ultimValNoi = new int[cpNou];

	for (int i = 0; i < cpChei; i++) {
		cheiNoi[i] = chei[i];
		urmCheiNoi[i] = urmChei[i];
		precCheiNoi[i] = precChei[i];
		primValNoi[i] = primVal[i];
		ultimValNoi[i] = ultimVal[i];
	}

	for (int i = cpChei; i < cpNou - 1; i++) {
		urmCheiNoi[i] = i + 1;
		precCheiNoi[i] = -1;
		primValNoi[i] = -1;
		ultimValNoi[i] = -1;
	}

	urmCheiNoi[cpNou - 1] = -1;
	precCheiNoi[cpNou - 1] = -1;
	primValNoi[cpNou - 1] = -1;
	ultimValNoi[cpNou - 1] = -1;

	primLiberChei = cpChei;

	delete[] chei;
	delete[] urmChei;
	delete[] precChei;
	delete[] primVal;
	delete[] ultimVal;

	chei = cheiNoi;
	urmChei = urmCheiNoi;
	precChei = precCheiNoi;
	primVal = primValNoi;
	ultimVal = ultimValNoi;
	cpChei = cpNou;
}

// Theta(cpValori)
void MD::redimValori() {
	int cpNou = cpValori * 2;

	TValoare* valoriNoi = new TValoare[cpNou];
	int* urmValoriNoi = new int[cpNou];
	int* precValoriNoi = new int[cpNou];

	for (int i = 0; i < cpValori; i++) {
		valoriNoi[i] = valori[i];
		urmValoriNoi[i] = urmValori[i];
		precValoriNoi[i] = precValori[i];
	}

	for (int i = cpValori; i < cpNou - 1; i++) {
		urmValoriNoi[i] = i + 1;
		precValoriNoi[i] = -1;
	}

	urmValoriNoi[cpNou - 1] = -1;
	precValoriNoi[cpNou - 1] = -1;

	primLiberValori = cpValori;

	delete[] valori;
	delete[] urmValori;
	delete[] precValori;

	valori = valoriNoi;
	urmValori = urmValoriNoi;
	precValori = precValoriNoi;

	cpValori = cpNou;
}

// Theta(1)
MD::MD() {
	cpChei = 10;
	cpValori = 10;

	chei = new TCheie[cpChei];
	urmChei = new int[cpChei];
	precChei = new int[cpChei];

	primVal = new int[cpChei];
	ultimVal = new int[cpChei];

	valori = new TValoare[cpValori];
	urmValori = new int[cpValori];
	precValori = new int[cpValori];

	primChei = -1;
	ultimChei = -1;
	primLiberChei = 0;
	primLiberValori = 0;
	nrPerechi = 0;


	for(int i=0; i<cpChei - 1; i++)
	{
		urmChei[i] = i+1;
		precChei[i] = -1;
		primVal[i] = -1;
		ultimVal[i] = -1;
	}
	urmChei[cpChei-1] = -1;
	precChei[cpChei - 1] = -1;
	primVal[cpChei - 1] = -1;
	ultimVal[cpChei - 1] = -1;

	for(int i=0; i<cpValori - 1; i++)
	{
		urmValori[i] = i+1;
		precValori[i] = -1;
	}
	urmValori[cpValori-1] = -1;
	precValori[cpValori - 1] = -1;

}

// O(nrChei)
void MD::adauga(TCheie c, TValoare v) {
	int i = primChei;
	while (i != -1 && chei[i] != c) {
		i = urmChei[i];
	}

	if (i != -1) {
		int pozVal = alocaValoare();
		valori[pozVal] = v;
		urmValori[pozVal] = -1;
		precValori[pozVal] = ultimVal[i];

		if (primVal[i] == -1) {
			primVal[i] = pozVal;
			ultimVal[i] = pozVal;
		}

		else {
			urmValori[ultimVal[i]] = pozVal;
			ultimVal[i] = pozVal;
		}
	}
	else {
		int pozCheie = alocaChei();
		chei[pozCheie] = c;
		urmChei[pozCheie] = -1;
		precChei[pozCheie] = ultimChei;

		if(primChei == -1)
		{
			primChei = pozCheie;
			ultimChei = pozCheie;
		}
		else
		{
			urmChei[ultimChei] = pozCheie;
			ultimChei = pozCheie;
		}

		int pozVal = alocaValoare();
		valori[pozVal] = v;
		urmValori[pozVal] = -1;
		precValori[pozVal] = -1;

		primVal[pozCheie] = pozVal;
		ultimVal[pozCheie] = pozVal;
	}

	nrPerechi++;
}

// O(nrChei + nrValoriPentruCheie)
bool MD::sterge(TCheie c, TValoare v) {

	int i = primChei;
	while (i != -1 && chei[i] != c) {
		i = urmChei[i];
	}
	if (i == -1) {
		return false;
	}

	int j = primVal[i];
	while (j != -1 && valori[j] != v) {
		j = urmValori[j];
	}
	if (j == -1) {
		return false;
	}

	if (precValori[j] != -1) {
		urmValori[precValori[j]] = urmValori[j];
	}
	else {
		primVal[i] = urmValori[j];
	}

	if (urmValori[j] != -1) {
		precValori[urmValori[j]] = precValori[j];
	}
	else {
		ultimVal[i] = precValori[j];
	}

	dealocaValoare(j);
	nrPerechi--;

	if (primVal[i] == -1) {
		if (precChei[i] != -1) {
			urmChei[precChei[i]] = urmChei[i];
		}
		else {
			primChei = urmChei[i];
		}

		if (urmChei[i] != -1) {
			precChei[urmChei[i]] = precChei[i];
		}
		else {
			ultimChei = precChei[i];
		}

		dealocaChei(i);
	}

	return true;
}

// O(nrChei + nrValoriPentruCheie)
vector<TValoare> MD::cauta(TCheie c) const {
	
	vector<TValoare> rez;
	int i = primChei;
	while(i!=-1 && chei[i] != c) {
		i = urmChei[i];
	}

	if(i != -1) {
		int j = primVal[i];
		while(j != -1) {
			rez.push_back(valori[j]);
			j = urmValori[j];
		}
	}

	return rez;
}

// Theta(1)
int MD::dim() const {
	return nrPerechi;
}

// Theta(1)
bool MD::vid() const {
	return primChei == -1;
}

// Theta(1)
IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}

vector<TValoare> MD::stergeValoriPentruCheie(TCheie cheie) {
	vector<TValoare> rez;
	int i = primChei;

	while (i != -1 && chei[i] != cheie) {
		i = urmChei[i];
	}

	if (i == -1) {
		return rez;
	}

	int j = primVal[i];
	TValoare valoare = valori[j];
	while(j != -1)
	{
		valoare = valori[j];
		rez.push_back(valoare);
		j = urmValori[j];
		sterge(cheie, valoare);
	}

	return rez;
}


MD::~MD() {
	delete[] chei;
	delete[] urmChei;
	delete[] precChei;
	delete[] primVal;
	delete[] ultimVal;

	delete[] valori;
	delete[] urmValori;
	delete[] precValori;
}

