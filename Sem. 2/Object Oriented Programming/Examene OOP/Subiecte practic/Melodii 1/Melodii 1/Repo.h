#pragma once

#include "Melodie.h"

#include <vector>
using std::vector;
#include <exception>
using std::exception;

class RepoException : public exception
{
	string message;
public:
	RepoException(string message) : message(message) {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Repo
{
	vector<Melodie> melodii;
	string fileName;

public:
	Repo(string fileName) : fileName{ fileName } {
		loadFile();
	}

	const vector<Melodie>& getAll() const;
	void modificaMelodie(int id, string titlu, int rank);
	void stergeMelodie(int id);

	void loadFile();
	void saveToFile();
};

