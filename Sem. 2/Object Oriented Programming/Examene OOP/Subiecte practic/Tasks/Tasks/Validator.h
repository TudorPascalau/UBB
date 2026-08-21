#pragma once
#include "Task.h"

#include <exception>
using std::exception;

class ValidatorException : public exception
{
	string message;
public:
	ValidatorException(string message) : message{ message } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Validator
{
public:
	void validate(int id, const string& descriere, const vector<string>& programatori, const string& stare);
};

