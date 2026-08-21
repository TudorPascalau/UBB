#pragma once

#include "Repo.h"

class Service
{
private:
	Repo& repo;
public:

	/*
	* Constructor pentru service
	* @param repo: repository asociat service-ului
	*/
	Service(Repo& repo) : repo{ repo } {}

	/*
	* Metoda ce returneaza toate articolele din service
	* @returns: vector<Articol> ce contine toate articolele
	*/
	vector<Articol> getAllArticole() {
		return repo.getAll();
	}

	/*
	* Metoda ce filtreaza articolele dupa un brand
	* @param brand: brand-ul dupa care se filtreaza
	* @returns: vector<Articol> ce contine articolele filtrate
	*/
	vector<Articol> filterByBrand(const string& brand);

	/*
	* Metoda ce sorteaza articolele dupa marime
	* @returns: vector<Articol> ce contine articolele sortate
	*/
	vector<Articol> sortByMarime();
};

