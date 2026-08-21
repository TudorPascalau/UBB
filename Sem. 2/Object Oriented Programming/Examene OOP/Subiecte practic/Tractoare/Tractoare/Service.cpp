#include "Service.h"

#include <algorithm>

vector<Tractor> Service::getSortatDenumire() const {
	auto tractoare = repo.getAll();

	sort(tractoare.begin(), tractoare.end(), [](const Tractor& t1, const Tractor& t2) {
		return t1.getDenumire() < t2.getDenumire();
		});

	return tractoare;
}

void Service::addTractor(int id, string denumire, string tip, int nrRoti) {
	val.validate(id, denumire, tip, nrRoti);
	Tractor t{ id, denumire, tip, nrRoti };
	repo.addRepo(t);
}

vector<string> Service::getTipuri() const
{
	vector<string> tipuri;
	auto tractoare = repo.getAll();
	for (const auto& t : tractoare) {
		if (find(tipuri.begin(), tipuri.end(), t.getTip()) == tipuri.end()) {
			tipuri.push_back(t.getTip());
		}
	}

	return tipuri;
}

void Service::decrementRoti(int id)
{
	repo.modificaRepo(id);
}
