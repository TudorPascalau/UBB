#pragma once

#include <iostream>
#include <vector>

struct A {
	A() { std::cout << "A"; }
	virtual void print() {
		std::cout << "A";
	}
};

struct B : public A {
	B() { std::cout << "B"; }
	void print() override {
		std::cout << "B";
	}
};

class C {
	int x;
public:
	C(int x) : x(x) {}
	void print() {
		std::cout << x << '\n';
	}
};

C f2(C c) {
	c.print();
	c = C{ 10 };
	c.print();
	return c;
}