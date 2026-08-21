#include "Service.h"

#include <algorithm>

vector<Rochie> Service::sortPret() const {
	vector<Rochie> rez = repo.getAll();
	std::sort(rez.begin(), rez.end(),
		[](const Rochie& r1, const Rochie& r2) {
			return r1.getPret() < r2.getPret();
		});

	return rez;
}

vector<Rochie> Service::sortMarime() const {
	vector<Rochie> rez = repo.getAll();
	std::sort(rez.begin(), rez.end(),
		[](const Rochie& r1, const Rochie& r2) {
			return r1.getMarime() < r2.getMarime();
		});

	return rez;
}