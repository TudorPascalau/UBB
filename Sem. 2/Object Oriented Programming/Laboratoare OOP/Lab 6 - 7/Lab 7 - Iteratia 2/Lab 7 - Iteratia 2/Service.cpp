#include <utility>

#include "Service.h"

void Service::addCarte(int id, const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ id, titlu, autor, gen, an };
	this->val.validate(c);
	this->rep.addCarte(c);
}

void Service::deleteCarte(int id) {
	this->rep.deleteCarte(id);
}

void Service::updateCarte(int id, const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ id, titlu, autor, gen, an };
	this->val.validate(c);
	this->rep.updateCarte(c);
}

const Carte& Service::findCarte(int id) const {
	return this->rep.getById(id);
}

const Lista<Carte>& Service::getAll() const {
	return this->rep.getAll();
}

Lista<int> Service::generalSort(const function<bool(const Carte&, const Carte&)>& cmp) const {
	Lista<int> rez;
	const Lista<Carte>& all = rep.getAll();

	for (int i = 0; i < all.size(); i++) {
		rez.add(i);
	}

	for (int i = 0; i < rez.size() - 1; i++) {
		for (int j = i + 1; j < rez.size(); j++) {
			int poz1 = rez.getElem(i);
			int poz2 = rez.getElem(j);

			if (!cmp(all.getElem(poz1), all.getElem(poz2))) {
				std::swap(rez.getElem(i), rez.getElem(j));
			}
		}
	}

	return rez;
}

Lista<int> Service::generalFilter(const function<bool(const Carte&)>& fct) const {
	Lista<int> rez;

	int poz = 0;
	for (const auto& carte : rep.getAll()) {
		if (fct(carte)) {
			rez.add(poz);
		}
		poz++;
	}

	return rez;
}

Lista<int> Service::sortByTitlu() const {
	return generalSort([](const Carte& c1, const Carte& c2) {
		return c1.getTitlu() < c2.getTitlu();
		});
}

Lista<int> Service::sortByAutor() const {
	return generalSort([](const Carte& c1, const Carte& c2) {
		return c1.getAutor() < c2.getAutor();
		});
}

Lista<int> Service::sortByAnGen() const {
	return generalSort([](const Carte& c1, const Carte& c2) {
		if (c1.getAn() == c2.getAn()) {
			return c1.getGen() < c2.getGen();
		}
		return c1.getAn() < c2.getAn();
		});
}

Lista<int> Service::filterByTitlu(const string& titlu) const {
	return generalFilter([&titlu](const Carte& c) {
		return c.getTitlu() == titlu;
		});
}

Lista<int> Service::filterByAn(int an) const {
	return generalFilter([an](const Carte& c) {
		return c.getAn() == an;
		});
}