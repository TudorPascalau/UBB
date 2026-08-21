#include "s1ex1.h"
#include "s1ex2.h"
#include "s1ex3.h"
#include "s1ex4.h"

#include <algorithm>
using std::sort;

// Ex 1
void ex1() {

	try {
		f1(-1);
		assert(false);
	}
	catch (std::exception& e) {
		assert(true);
	}

	try {
		f1(0);
		assert(false);
	}
	catch (std::exception& e) {
		assert(true);
	}

	assert(f1(123) == 321);
}

void ex2() {
	// a)
	try {
		cout << except(1 < 1); //3
		cout << except(true); // exceptie
		cout << except(false);
	}
	catch (int ex) {
		cout << ex; //2
	}
	cout << 4; // 4
	cout << '\n';

	//b)
	f2(); //AA - doi constructori, print, ~A~A doi destructori RAII
}

void ex3() {
	auto v = smoothies();
	sort(v.begin(), v.end(), [](Smoothy* a, Smoothy* b) {
		return a->descriere() < b->descriere();
		});

	for (auto s : v) {
		cout << s->descriere() << " " << s->getPret() << "\n";
		delete s;
	}
}

void ex4() {
	Geanta<string> geanta{ "Ion" };
	geanta = geanta + string{ "haine" };
	geanta + string{ "pahar" };
	for (auto o : geanta) {
		cout << o << "\n";
	}
}

// Ex 3 - polimorfism, decorator, lambda, sortare, vector de pointeri la obiecte
int main() {
	ex1();
	ex2();
	ex3();
	ex4();

	return 0;
}