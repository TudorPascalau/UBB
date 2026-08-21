#pragma once

#include "Carte.h"

#include <vector>
using std::vector;

#include <exception>
using std::exception;

class RepoException : public exception
{
private:
	string message;
public:
	RepoException(string message) : message{ message } {}
	const string& getMessage() const noexcept { 
		return message; 
	}
	~RepoException() = default;
};

class Repo
{
private:
	vector<Carte> carti;
	string filename;

	void loadFromFile();
	void saveToFile();

public:
	Repo(string filename) : filename{ filename } {
		loadFromFile();
	};
	~Repo() {};

	void adauga(const Carte& c);
	vector<Carte> getAll() const;
};


