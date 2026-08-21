#include "Repo.h"

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::stringstream;

using std::getline;

void Repo::loadFromFile() {
	ifstream fin(filename);
	if (!fin.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!");
	}

	string line;
	while (getline(fin, line)) {
		if (line.empty()) {
			continue;
		}

		stringstream ss(line);
		string codStr, categorie, brand, marime;

		getline(ss, codStr, ',');
		getline(ss, categorie, ',');
		getline(ss, brand, ',');
		getline(ss, marime, ',');

		int cod = stoi(codStr);

		articole.emplace_back(cod, categorie, brand, marime);
	}
	
}
