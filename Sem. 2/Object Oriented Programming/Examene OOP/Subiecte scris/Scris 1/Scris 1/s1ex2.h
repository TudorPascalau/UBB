#pragma once

#include <iostream>
using namespace std;

/*
*  Functie care primeste un numar intreg si returneaza numarul format din cifrele lui, dar in ordine inversa.
*  @throws std::exception daca numarul este negativ sau zero.
*  @param x numarul intreg de procesat
*/
int except(bool thrEx) {
	if (thrEx) {
		throw 2;
	}
	return 3;
}

class A {
public:
	A() { cout << "A" << endl; }
	~A() { cout << "~A" << endl; }
	void print() {
		cout << "print" << endl;
	}
};

void f2() {
	A a[2];
	a[1].print();
}

