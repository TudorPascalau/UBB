#pragma once

#include "Rochie.h"

#include <vector>
using std::vector;
#include <exception>
using std::exception;

class RepoError : public exception {
private:
	string message;
public:
	RepoError(const string& msg) : message{ msg } {};
	string getMessage() const noexcept {
		return message;
	}
};

class Repo
{
private:
	vector<Rochie> rochii;
	string file;

	void loadFromFile(const string& filename);
	void saveToFile(const string& filename);

public:
	Repo(const string& filename) : file{ filename } {
		loadFromFile(file);
	};

	void addRochie(const Rochie& rochie);
	void inchireazaRochie(int cod);

	const vector<Rochie>& getAll() const noexcept{
		return rochii;
	}

	vector<Rochie>& getAll() {
		return rochii;
	}

	~Repo() {};
};

