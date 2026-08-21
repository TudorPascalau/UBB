#pragma once
#include "Melodie.h"

#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
using std::ofstream;
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
	vector<Melodie> melodii;
	string fileName;

public:
	Repo(string fileName) : fileName{ fileName } {
		loadFile();
	}

	void loadFile();
	void savetoFile();

	const vector<Melodie>& getAll() {
		return melodii;
	}

	void addRepo(Melodie& m);
	void stergeRepo(int id);
};

