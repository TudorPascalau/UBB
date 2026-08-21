#include "Repo.h"

#include <fstream>
#include <sstream>

void Repo::loadFile()
{
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		throw(RepoException("Error opening file"));
	}

	string line;
	while (getline(fin, line)) {
		string idStr, nume, tip, pretStr;
		std::stringstream ss(line);

		getline(ss, idStr, ',');
		getline(ss, nume, ',');
		getline(ss, tip, ',');
		getline(ss, pretStr, ',');

		int id = stoi(idStr);
		double pret = stod(pretStr);

		produse.emplace_back(id, nume, tip, pret);
	}

	fin.close();
}

void Repo::saveToFile()
{
	std::ofstream fout(filename);
	if (!fout.is_open()) {
		throw(RepoException("Error opening file"));
	}

	for (const auto& p : produse) {
		fout << p.getId() << ',' << p.getNume() << ',' << p.getTip() << ',' << p.getPret() << '\n';
	}

	fout.close();
}

void Repo::addRepo(int id, string nume, string tip, double pret)
{
	for (const auto& p : produse) {
		if (p.getId() == id) {
			throw(RepoException("Id deja existent! "));
		}
	}

	produse.emplace_back(id, nume, tip, pret);
	saveToFile();
}
