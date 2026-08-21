// === Validator.h ===
#pragma once
#include "Produs.h"

#include <exception>
#include <string>
using std::exception;
using std::string;

class ValidatorException : public exception {
    string message;
public:
    explicit ValidatorException(string message) : message{ std::move(message) } {}
    const char* what() const noexcept override { return message.c_str(); }
};

class Validator {
public:
    void validate(const Produs& e) const;
};

// === Validator.cpp ===
#include "Validator.h"

void Validator::validate(const Produs& e) const {
    string errors;

    if (e.getId() < 0) {
        errors += "Id invalid! ";
    }
    if (e.getNume().empty()) {
        errors += "Nume vid! ";
    }
    if (e.getTip().empty()) {
        errors += "Tip vid! ";
    }
    if (e.getPret() <= 0) {
        errors += "Pret invalid! ";
    }

    if (!errors.empty()) {
        throw ValidatorException{ errors };
    }
}
