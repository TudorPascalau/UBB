#pragma once

#include "Tractor.h"

#include <vector>
using std::vector;

#include <exception>
using std::exception;	

class RepoException : public exception
{
	string message;
public:
	RepoException(const string& msg) : message{ msg } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Repo
{
	vector<Tractor> tractoare;
	string fileName;

public:
	Repo(string fileName) : fileName{ fileName } {
		loadFromFile();
	}

	void loadFromFile();
	void saveToFile();

	const vector<Tractor>& getAll() const { 
		return tractoare; 
	}

	void addRepo(const Tractor& t);
	void modificaRepo(int id);
};

