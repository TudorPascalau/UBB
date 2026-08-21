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
	/*
	* Constructor pentru exceptia custom de eroare repository
	* @param message : mesajul exceptiei
	*/
	RepoException(string message) : message{ message } {}

	/*
	* Metoda pentru accesarea mesajului erorii
	* @return mesajul erorii : char*
	*/
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Repo
{
	vector<Task> tasks;
	string filename;
public:

	/*
	* Constructor pentru repository
	* @param filename: numele fisierului care contina task-urile
	* Post: Se incarca in repository intern toate task-urile
	*/
	Repo(string filename) : filename{ filename } {
		loadFile();
	}

	/*
	* Metoda ce citeste din fisier toate task-urile
	* @throws RepoException: daca nu se poate deschide fisierul
	*/
	void loadFile();

	/*
	* Metoda ce suprascrie in fisier toate task-urile
	* @throws RepoException: daca nu se poate deschide fisierul
	*/
	void saveToFile();

	/*
	* Metoda care ofera toate task-urile
	* @return lista cu toate Task-uri: vector<Task> 
	*/
	const vector<Task>& getAll() {
		return tasks;
	}

	/*
	* Metoda care adauga in repository un Task
	* @param id, descriere, programatori, stare : campurile Task-ului
	* @throws RepoException: daca exista deja un task cu id dat
	*/
	void addRepo(int id, const string& descriere, const vector<string>& programatori, const string& stare);

	/*
	* Metoda care modifica starea unui Task
	* @param id: id-ul Task-ului de modificat
	* @param newStare: starea noua
	*/
	void modificaStare(int id, const string& newStare);
};

