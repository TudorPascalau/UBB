#include "Repo.h"

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::stringstream;

void Repo::loadFromFile()
{
	ifstream fin(fileName);
	if (!fin.is_open())
		throw RepoException("Error opening file for reading!");

	string line;
	while (std::getline(fin, line)) {
		stringstream ss(line);
		string idStr, denumire, tip, nrRotiStr;
		getline(ss, idStr, ',');
		getline(ss, denumire, ',');
		getline(ss, tip, ',');
		getline(ss, nrRotiStr, ',');

		int id = stoi(idStr);
		int nrRoti = stoi(nrRotiStr);

		tractoare.emplace_back(id, denumire, tip, nrRoti);
	}
	fin.close();
}

void Repo::saveToFile() {
	ofstream fout(fileName);
	if (!fout.is_open())
		throw RepoException("Error opening file for writing!");

	for (const auto& tractor : tractoare) {
		fout << tractor.getId() << ","
			<< tractor.getDenumire() << ","
			<< tractor.getTip() << ","
			<< tractor.getNrRoti() << "\n";
	}
	fout.close();
}

void Repo::addRepo(const Tractor& t)
{
	int id = t.getId();
	for (const auto& t : tractoare) {
		if (t.getId() == id) {
			throw RepoException("Exista tractor cu acelasi id!");
		}
	}

	tractoare.push_back(t);
	saveToFile();
}

void Repo::modificaRepo(int id)
{
	for (auto& t : tractoare) {
		if (t.getId() == id) {
			int nr = t.getNrRoti();
			if (nr > 2) {
				t.setNrRoti(nr - 2);
				// persist change
				saveToFile();
			}
			else {
				throw(RepoException("Prea putine roti!"));
			}
		}
	}
}
