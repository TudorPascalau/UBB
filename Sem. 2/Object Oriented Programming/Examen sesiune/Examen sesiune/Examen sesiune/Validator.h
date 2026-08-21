#pragma once
#include "Task.h"

#include <exception>
using std::exception;

class ValidatorException : public exception
{
	string message;
public:
	/*
	* Constructor pentru exceptia custom de eroare validator
	* @param message : mesajul exceptiei
	*/
	ValidatorException(string message) : message{ message } {}

	/*
	* Metoda pentru accesarea mesajului erorii
	* @return mesajul erorii : char*
	*/
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Validator
{
public:
	/*
	* Metoda care valideaza campurile unui Task
	* @param id, descriere, programatori, stare : campurile unui Task
	* @param id: int
	* @param descriere: string, nevida
	* @param programatori: dimensiune minim 1, maxim 4
	* @param stare: apartine {open, closed, inprogress}
	* @throws ValidatorException: daca nu sunt respectacte preconditii parametri
	*/
	void validate(int id, const string& descriere, const vector<string>& programatori, const string& stare);
};

