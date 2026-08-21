#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <random>
#include <chrono>
#include <map>
#include <fstream>


#include "Service.h"

void Service::addCarte(int id, const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ id, titlu, autor, gen, an };
	this->val.validate(c);
	this->rep.addCarte(c);
}

void Service::deleteCarte(int id) {
	this->rep.deleteCarte(id);
	this->cos.stergeId(id);
}

void Service::updateCarte(int id, const string& titlu, const string& autor, const string& gen, int an) {
	
	const Carte& carteVeche = rep.getById(id);
	const string titluVechi = carteVeche.getTitlu();
	
	Carte c{ id, titlu, autor, gen, an };
	this->val.validate(c);
	this->rep.updateCarte(c);

	if (titluVechi != titlu)
		cos.stergeId(id);
}

const Carte& Service::findCarte(int id) const {
	return this->rep.getById(id);
}

const Lista<Carte>& Service::getAll() const noexcept{
	return this->rep.getAll();
}

Lista<int> Service::generalSort(const function<bool(const Carte&, const Carte&)>& cmp) const{
	const Lista<Carte>& all = rep.getAll();

	std::vector<int> pozitii(static_cast<size_t>(all.size()));
	std::iota(pozitii.begin(), pozitii.end(), 0);

	std::sort(pozitii.begin(), pozitii.end(),
		[&all, &cmp](int poz1, int poz2) {
			return cmp(all.getElem(poz1), all.getElem(poz2));
		});

	Lista<int> rez;
	for (const int poz : pozitii) {
		rez.add(poz);
	}

	return rez;
}

Lista<int> Service::generalFilter(const function<bool(const Carte&)>& fct) const{
	const Lista<Carte>& all = rep.getAll();

	std::vector<int> pozitii(static_cast<size_t>(all.size()));
	std::iota(pozitii.begin(), pozitii.end(), 0);

	std::vector<int> filtrate;
	std::copy_if(pozitii.begin(), pozitii.end(), std::back_inserter(filtrate),
		[&all, &fct](int poz) {
			return fct(all.getElem(poz));
		});

	Lista<int> rez;
	for (const int poz : filtrate) {
		rez.add(poz);
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

Lista<int> Service::sortByAnGen() const{
	return generalSort([](const Carte& c1, const Carte& c2){
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

void Service::adaugaCos(const string& titlu) {
	const Lista<Carte>& all = rep.getAll();

	auto it = std::find_if(all.begin(), all.end(),
		[&titlu](const Carte& c) {
			return c.getTitlu() == titlu;
		});
	if (it == all.end()) {
		throw RepoError("Nu exista carte cu acest titlu\n");
	}

	int id = it->getId();
	this->cos.adauga(id);
}

void Service::golesteCos() noexcept {
	this->cos.goleste();
}

void Service::genereazaCos(int nr) {
	const Lista<Carte>& all = rep.getAll();
	if (all.size() == 0) {
		return;
	}
	
	std::vector<int> pozitii(static_cast<size_t>(all.size()));
	std::iota(pozitii.begin(), pozitii.end(), 0);

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(pozitii.begin(), pozitii.end(), std::default_random_engine(static_cast<unsigned int>(seed)));

	cos.goleste();

	std::for_each(pozitii.begin(), pozitii.begin() + nr,
		[&all, this](int i) {
			int poz = i % all.size();
			cos.adauga(all.getElem(poz).getId());
		});
}

const Lista<int>& Service::getCos() const noexcept {
	return cos.getAll();
}

int Service::sizeCos() const noexcept {
	return cos.size();
}

void Service::exportCosCSV(const string& numeFisier) const {
	std::ofstream out(numeFisier);
	if (!out.is_open()) {
		throw RepoError("Nu s-a putut deschide fisierul pentru scriere.\n");
	}

	out << "id,titlu,autor,gen,an\n";

	const Lista<int>& cosIds = cos.getAll();
	const Lista<Carte>& all = rep.getAll();

	for (const int id : cosIds) {
		auto it = std::find_if(all.begin(), all.end(),
			[id](const Carte& c) {
				return c.getId() == id;
			});

		if (it != all.end()) {
			out << it->getId() << ','
				<< it->getTitlu() << ','
				<< it->getAutor() << ','
				<< it->getGen() << ','
				<< it->getAn() << '\n';
		}
	}

	out.close();
}

Lista<DTORaport> Service::raportGen() const {
	const Lista<Carte>& all = rep.getAll();

	std::map<string, int> genCount;

	for (const Carte& c : all) {
		genCount[c.getGen()]++;
	}

	Lista<DTORaport> raport;
	for (const auto& pereche : genCount) {
		raport.add(DTORaport(pereche.first, pereche.second));
	}
	return raport;
}