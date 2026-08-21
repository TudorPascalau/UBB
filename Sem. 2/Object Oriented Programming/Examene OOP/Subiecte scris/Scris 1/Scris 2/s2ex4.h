#pragma once

#include <vector>
using std::vector;

template <typename T>
class Measurement 
{
private:
	T valoare;
public:
	Measurement(T valoare) : valoare(valoare) {}

	Measurement& operator+(const T& ot) {
		valoare = valoare + ot;
		return *this;
	}

	bool operator<(const Measurement ot) {
		return valoare < ot.valoare;
	}

	T value() const {
		return valoare;
	}
};