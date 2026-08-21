#pragma once
#include "Task.h"

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
	vector<Task> tasks;
	string filename;
public:
	Repo(string filename) : filename{ filename } {
		loadFile();
	}

	void loadFile();
	void saveToFile();

	const vector<Task>& getAll() {
		return tasks;
	}

	void addRepo(int id, const string& descriere, const vector<string>& programatori, const string& stare);
	void modificaStare(int id, const string& newStare);
};

