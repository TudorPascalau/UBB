#include "Repo.h"

int Repo::findPozById(int id) const {
	int poz = 0;
	for (const auto& carte : this->repo) {
		if (carte.getId() == id) {
			return poz;
		}
		poz++;
	}

	return -1;
}

int Repo::repoSize() const {
	return this->repo.size();
}


void Repo::addCarte(const Carte& c) {
	int poz = findPozById(c.getId());
	if (poz != -1)
		throw RepoError("Exista deja o carte cu acest id.\n");

	this->repo.add(c);
}

void Repo::deleteCarte(int id) {
	int poz = findPozById(id);
	if (poz == -1)
		throw RepoError("Nu exista carte cu acest id.\n");

	this->repo.remove(poz);
}

void Repo::updateCarte(const Carte& c) {
	int poz = findPozById(c.getId());
	if (poz == -1)
		throw RepoError("Nu exista carte cu acest id.\n");

	Carte& updateCarte = this->repo.getElem(poz);
	updateCarte.setTitlu(c.getTitlu());
	updateCarte.setAutor(c.getAutor());
	updateCarte.setGen(c.getGen());
	updateCarte.setAn(c.getAn());
}

const Carte& Repo::getById(int id) const {
	int poz = findPozById(id);
	if (poz == -1)
		throw RepoError("Nu exista carte cu acest id.\n");

	return this->repo.getElem(poz);
}

const Lista<Carte>& Repo::getAll() const {
	return this->repo;
}