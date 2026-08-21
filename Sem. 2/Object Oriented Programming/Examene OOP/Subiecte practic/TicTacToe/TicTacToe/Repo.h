#pragma once

#include "XO.h"

#include <vector>
using std::vector;

#include <fstream>
#include <sstream>

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
	vector<XO> jocuri;
	string filename;
public:
	Repo(string filename) : filename{ filename } {
		loadFile();
	}

	void loadFile();
	void saveToFile();

	const vector<XO>& getAll() {
		return jocuri;
	}

	void addRepo(int id, int dim, string table, string player, string stare) {
		jocuri.emplace_back(id, dim, table, player, stare);
		saveToFile();
	}

	void modificaRepo(int id, int dim, string table, string player, string stare);
};

