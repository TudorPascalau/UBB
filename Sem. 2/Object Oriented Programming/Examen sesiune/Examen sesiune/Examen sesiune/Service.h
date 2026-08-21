#pragma once
#include "Repo.h"
#include "Validator.h"

#include <algorithm>

class Service
{
	Repo& repo;
	Validator& val;
public:
	/*
	* Constructor pentru service
	* @param repo: repository asociat service-ului
	* @param val: validator asociat service-ului
	*/
	Service(Repo& repo, Validator& val) : repo{ repo }, val{ val } {}

	/*
	* Metoda ce sorteaza task-urile dupa stare
	* @return: lista cu Task-uri sortate
	*/
	vector<Task> getSortatStare() const;

	/*
	* Metoda ce filtreaza task-urile ce au programatori cu un anumit nume
	* @param nume: numele dupa care filtram
	* @rreturn: lista cu task-urile sortate si filtrate
	*/
	vector<Task> filterNume(const string& nume) const;

	/*
	* Metoda ce adauga un Task
	* @param id, descriere, programatori, stare: campuri Task de adaugat
	* @throws RepoException: daca exista deja task cu id dat
	* @throws ValidatorException: daca parametrii nu sunt valizi
	*/
	void adauga(int id, const string& descriere, const vector<string>& programatori, const string& stare);

	/*
	* Metoda care modifica starea unui Task
	* @param id: id-ul Task-ului de modificat
	* @param newStare: starea noua
	*/
	void modifica(int id, const string& newStare) {
		repo.modificaStare(id, newStare);
	}
};

