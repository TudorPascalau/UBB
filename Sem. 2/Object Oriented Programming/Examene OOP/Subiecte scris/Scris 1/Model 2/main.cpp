#include "m2ex2.h"

void ex2a() {
	A* o1 = new A();
	A* o2 = new B();
	o1->print();
	o2->print();
	delete o1;
	delete o2;
}

void ex2b() {
	deque<string> s;
	s.push_back("1");
	s.push_back("2");
	s.push_back("3");
	s.push_front("1");
	s.push_front("4");
	auto it = s.begin();
	auto end = s.end();
	end = end - 1; it++;
	while (it != end) {
		cout << *it;
		it++;
	}
}

int main() {

	ex2a();
	ex2b();

	return 0;
}