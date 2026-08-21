#pragma once

#include "Articol.h"

#include <vector>
using std::vector;

#include <exception>
using std::exception;

class RepoException : public exception
{
private:
	string message;
public:
	/*
	* Constructor pentru custom RepoException
	* @param message: mesajul exceptiei / erorii
	*/
	RepoException(string message) : message{ message } {}

	/*
	* Getter pentru mesajul unei exceptii RepoException
	* @returns: mesajul exceptiei / erorii
	*/
	string getMessage() const noexcept {
		return message;
	}
};

class Repo
{
private:
    vector<Articol> articole;
	string filename;

	/*
	* Functie care citeste din fisierul asociat Repo-ului articole
	* pre: filename este valid
	* post: se adauga in Repository intern articolele asociate datelor din fisierul filename
	*/
	void loadFromFile();

public:

	/*
	* Constructor pentru Repository
	* @param filename: fisierul cu datele cartilor
	*/
	Repo(string filename) : filename{ filename } {
		loadFromFile();
	}

	/*
	* Metoda ce returneaza toate articolele din repo
	* @returns: vector de Articol cu toate articolele
	*/
	vector<Articol> getAll() const {
		return articole;
	}
};

