#include "Service.h"

#include <algorithm>

vector<Melodie> Service::getSortRank() const
{
	auto rez = repo.getAll();
	sort(rez.begin(), rez.end(), [](Melodie& a, Melodie& b) {
		return a.getRank() < b.getRank();
		});

	return rez;
}

void Service::sterge(int id)
{
	bool ok = false;
	string artist = "";
	auto all = repo.getAll();
	for (const auto& m : all) {
		if (m.getId() == id) {
			artist = m.getArtist();
		}
	}

	for (const auto& m : all) {
		if (m.getId() != id && m.getArtist() == artist) {
			ok = true;
		}
	}

	if (ok) {
		repo.stergeMelodie(id);
	}
	else {
		throw(RepoException("Ultima melodie de la artist"));
	}
}
