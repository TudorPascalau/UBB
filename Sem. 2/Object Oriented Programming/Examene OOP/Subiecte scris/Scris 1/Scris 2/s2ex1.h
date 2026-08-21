#pragma once

#include <utility>
#include <vector>
#include <exception>

std::pair<int, int> f(std::vector<int> l) {
	if (l.size() < 2) throw std::exception{};
	std::pair<int, int> rez{ -1, -1 };
	for (auto el : l) {
		if (el < rez.second) continue;
		if (rez.first < el) {
			rez.second = rez.first;
			rez.first = el;
		}
		else {
			rez.second = el;
		}
	}
	return rez;
}