#pragma once
#include "Produs.h"

#include <vector>
using std::vector;
#include <exception>
using std::exception;

class RepoException : public exception
{
	string message;
public:
	RepoException(string message) : message{ message } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Repo
{
	vector<Produs> produse;
	string filename;

public:
	Repo(string filename) : filename{ filename } {
		loadFile();
	}

	void loadFile();
	void saveToFile();

	const vector<Produs>& getAll() {
		return produse;
	}

	void addRepo(int id, string nume, string tip, double pret);
};

