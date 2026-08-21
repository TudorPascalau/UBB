#pragma once

#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;
using std::cout;

template <typename T>
class Geanta {
	string proprietar;
	vector<T> obiecte;
public:
	Geanta(const string& proprietar) : proprietar(proprietar) {}

	Geanta& operator+(const T& obiect) {
		obiecte.push_back(obiect);
		return *this;
	}

	auto begin() const {
		return obiecte.begin();
	}

	auto end() const {
		return obiecte.end();
	}
};
