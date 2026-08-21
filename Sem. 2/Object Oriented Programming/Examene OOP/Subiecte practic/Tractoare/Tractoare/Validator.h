#pragma once

#include "Tractor.h"

#include <exception>
using std::exception;

class ValidatorException : public exception
{
	string message;
public:
	ValidatorException(const string& msg) : message{ msg } {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class Validator
{
public:
	Validator() = default;

	void validate(int id, const string& denumire, const string& tip, int nrRoti) const;

	~Validator() = default;
};

