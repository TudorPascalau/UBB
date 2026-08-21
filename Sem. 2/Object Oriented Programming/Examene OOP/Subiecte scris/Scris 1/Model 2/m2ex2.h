#pragma once

#include <iostream>
#include <string>
#include <deque>
using namespace std;

class A {
public:
	virtual void print() {
		cout << "printA" << endl;
	}
	~A() { cout << "~A" << endl; }
};

class B : public A {
public:
	void print() {
		cout << "printB" << endl;
	}
	virtual ~B() {
		cout << "~B" << endl;
	}
};