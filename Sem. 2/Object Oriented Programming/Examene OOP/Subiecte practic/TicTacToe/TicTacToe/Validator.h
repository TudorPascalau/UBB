#pragma once
#include "XO.h"

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
	void validate(int dim, string table, string player, string stare);
};

