#include <algorithm>
#include <iterator>

#include "Repo.h"

int Repo::findPozById(int id) const noexcept{
	auto it = std::find_if(repo.begin(), repo.end(),
		[id](const Carte& carte) {
			return carte.getId() == id;
		});

	if (it == repo.end()) {
		return -1;
	}

	return static_cast<int>(std::distance(repo.begin(), it));
}

int Repo::repoSize() const noexcept{
	return this->repo.size();
}

void Repo::addCarte(const Carte& c) {
	if (findPozById(c.getId()) != -1) {
		throw RepoError("Exista deja o carte cu acest id.\n");
	}

	this->repo.add(c);
}

void Repo::deleteCarte(int id) {
	const int poz = findPozById(id);
	if (poz == -1) {
		throw RepoError("Nu exista carte cu acest id.\n");
	}

	this->repo.remove(poz);
}

void Repo::updateCarte(const Carte& c) {
	const int poz = findPozById(c.getId());
	if (poz == -1) {
		throw RepoError("Nu exista carte cu acest id.\n");
	}

	Carte& updateCarte = this->repo.get(poz);
	updateCarte.setTitlu(c.getTitlu());
	updateCarte.setAutor(c.getAutor());
	updateCarte.setGen(c.getGen());
	updateCarte.setAn(c.getAn());
}

const Carte& Repo::getById(int id) const {
	auto it = std::find_if(repo.begin(), repo.end(),
		[id](const Carte& carte) {
			return carte.getId() == id;
		});

	if (it == repo.end()) {
		throw RepoError("Nu exista carte cu acest id.\n");
	}

	return *it;
}

const Lista<Carte>& Repo::getAll() const noexcept{
	return this->repo;
}