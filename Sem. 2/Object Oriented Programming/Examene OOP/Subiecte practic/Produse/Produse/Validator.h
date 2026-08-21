#pragma once
#include "Produs.h"

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
	void validate(string nume, double pret) const;
};

