#pragma once

#include <iostream>
using std::cout;

#include <string>
using std::string;

class ClassB
{
private:
	int b;
public:
	ClassB(int b) : b{ b } {};
	virtual void Afisare() {
		cout << b << '\n';
	}
	virtual ~ClassB() {};
};

class ClassD : public ClassB
{
private:
	string d;
public:
	ClassD(int b, string d) : ClassB{ b }, d{ d } {};
	void Afisare() override {
		ClassB::Afisare();
		cout << d << '\n';
	}
};
