#include <fstream>
#include <sstream>

#include "FileRepo.h"

FileRepo::FileRepo(RepoAbstract& repo, const string& fileName) : repo{ repo }, fileName{ fileName } {
	loadFromFile();
}

void FileRepo::loadFromFile() {
	std::ifstream in(fileName);
	if (!in.is_open()) {
		return;
	}

	string idLine;
	while (std::getline(in, idLine)) {
		if (idLine.empty()) {
			continue;
		}

		string titlu;
		string autor;
		string gen;
		string anLine;

		if (!std::getline(in, titlu) || !std::getline(in, autor) || !std::getline(in, gen) || !std::getline(in, anLine)) {
			throw RepoError("Fisierul nu are format valid.\n");
		}

		int id = 0;
		int an = 0;
		std::stringstream idStream(idLine);
		std::stringstream anStream(anLine);
		if (!(idStream >> id) || !(anStream >> an)) {
			throw RepoError("Fisierul nu are format valid.\n");
		}

		repo.addCarte(Carte{ id, titlu, autor, gen, an });
	}
}

void FileRepo::writeToFile() const {
	std::ofstream out(fileName);
	if (!out.is_open()) {
		throw RepoError("Nu s-a putut deschide fisierul pentru scriere.\n");
	}

	for (const Carte& c : getAll()) {
		out << c.getId() << '\n'
			<< c.getTitlu() << '\n'
			<< c.getAutor() << '\n'
			<< c.getGen() << '\n'
			<< c.getAn() << '\n';
	}
}

void FileRepo::addCarte(const Carte& c) {
	repo.addCarte(c);
	writeToFile();
}

void FileRepo::deleteCarte(int id) {
	repo.deleteCarte(id);
	writeToFile();
}

void FileRepo::updateCarte(const Carte& c) {
	repo.updateCarte(c);
	writeToFile();
}

int FileRepo::repoSize() const {
	return repo.repoSize();
}

const Carte& FileRepo::getById(int id) const {
	return repo.getById(id);
}

const Lista<Carte>& FileRepo::getAll() const {
	return repo.getAll();
}
