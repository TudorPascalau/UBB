#include "s2ex1.h"
#include "s2ex2.h"
#include "s2ex3.h"
#include "s2ex4.h"

#include <algorithm>
#include <iostream>
#include <cassert>;
using std::cout;

void ex1() {
	/*
	* Functia f determina cele mai mari doua numere dintr-o lista data;
	* @param l - lista de numere
	* @throws std::exception daca lista are mai putin de 2 elemente
	* @return o pereche de numere, unde primul element este cel mai mare numar din lista, iar al doilea element este al doilea cel mai mare numar din lista
	*/

	std::vector<int> v1{ 1,2,3,4,5 };
	std::vector<int> v2{ 6 };
	auto rez = f(v1);
	assert(rez.first == 5 && rez.second == 4);
	try {
		rez = f(v2);
		assert(false);
	}
	catch (std::exception) {
		assert(true);
	}
}

void ex2() {
	// a)
	std::vector<A> v;
	v.push_back(A{}); // A - la creare
	v.push_back(B{}); // AB - creare tip A, peste care tip B
	for (auto& el : v) el.print(); //AA - in vector avem doar struct de tip A
	cout << '\n';

	// b)
	C c{ 4 };
	c.print(); // 4
	f2(c);	 // 4 10
	c.print(); // 4
	cout << '\n';
}

void ex3() {
	auto v = menus();
	std::sort(v.begin(), v.end(), [](Meniu* a, Meniu* b) {
		return a->getPret() > b->getPret();
		});

	for (auto m : v) {
		cout << m->descriere() << " " << m->getPret() << '\n';
		delete m;
	}
}

void ex4() {
	vector<Measurement<int>> v{ 10,2,3 };
	v[2] + 3 + 2;
	std::sort(v.begin(), v.end());
	for (const auto& m : v) cout << m.value() << ',';
}

int main() {
	ex1();
	ex2();
	ex3();
	ex4();

	return 0;
}