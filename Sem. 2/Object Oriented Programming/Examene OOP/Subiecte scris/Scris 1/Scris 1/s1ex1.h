#pragma once

#include <exception>
#include <cassert>


int f1(int x) {
	if (x <= 0)
		throw std::exception("Invalid argument");

	int rez = 0;
	while (x) {
		rez = rez * 10 + x % 10;
		x /= 10;
	}
	return rez;
}
