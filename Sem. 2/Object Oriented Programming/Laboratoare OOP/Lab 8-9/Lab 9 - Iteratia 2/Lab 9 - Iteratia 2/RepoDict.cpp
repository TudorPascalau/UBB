#include "RepoDict.h"

RepoDict::RepoDict(double probabilitate) : probabilitate{ probabilitate }, randomGenerator{ std::random_device{}() } {
	if (probabilitate < 0 || probabilitate > 1) {
		throw RepoError("Probabilitatea trebuie sa fie intre 0 si 1.\n");
	}
}

void RepoDict::maybeThrow() const {
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	if (dist(randomGenerator) < probabilitate) {
		throw RepoError("Exceptie random din RepoDict.\n");
	}
}

void RepoDict::refreshAll() {
	allCarti.clear();
	for (const auto& pereche : carti) {
		allCarti.add(pereche.second);
	}
}

int RepoDict::repoSize() const {
	maybeThrow();
	return static_cast<int>(carti.size());
}

void RepoDict::addCarte(const Carte& c) {
	maybeThrow();
	const int id = c.getId();
	if (carti.find(id) != carti.end()) {
		throw RepoError("Exista deja o carte cu acest id.\n");
	}

	carti.insert({ id, c });
	refreshAll();
}

void RepoDict::deleteCarte(int id) {
	maybeThrow();
	const auto it = carti.find(id);
	if (it == carti.end()) {
		throw RepoError("Nu exista carte cu acest id.\n");
	}

	carti.erase(it);
	refreshAll();
}

void RepoDict::updateCarte(const Carte& c) {
	maybeThrow();
	const int id = c.getId();
	const auto it = carti.find(id);
	if (it == carti.end()) {
		throw RepoError("Nu exista carte cu acest id.\n");
	}

	it->second = c;
	refreshAll();
}

const Carte& RepoDict::getById(int id) const {
	maybeThrow();
	const auto it = carti.find(id);
	if (it == carti.end()) {
		throw RepoError("Nu exista carte cu acest id.\n");
	}

	return it->second;
}

const Lista<Carte>& RepoDict::getAll() const {
	maybeThrow();
	return allCarti;
}
