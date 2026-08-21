#pragma once
#include <string>
using std::string;

class DTORaport
{
private:
	string gen;
	int count;

public: 
	DTORaport(const string& gen, int count) : gen{ gen }, count{ count } {}

	string getGen() const noexcept {
		return gen;
	}
	int getCount() const noexcept {
		return count;
	}
};

