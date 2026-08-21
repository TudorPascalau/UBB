#include "Repo.h"

#include <sstream>
using std::stringstream;

#include <algorithm>

void Repo::loadFile()
{
	ifstream fin(fileName);
	if (!fin.is_open()) {
		return;
	}

	string line;
	while (getline(fin, line)) {
		stringstream ss(line);
		string idStr, titlu, artist, gen;
		getline(ss, idStr, ',');
		getline(ss, titlu, ',');
		getline(ss, artist, ',');
		getline(ss, gen, ',');

		int id = stoi(idStr);
		melodii.emplace_back(id, titlu, artist, gen);
	}
	fin.close();
}

void Repo::savetoFile()
{
	ofstream fout(fileName);
	if (!fout.is_open()) {
		return;
	}

	for (const auto& m : melodii) {
		fout << m.getId() << ',' << m.getTitlu() << ',' << m.getArtist() << ',' << m.getGen() << '\n';
	}

	fout.close();
}

void Repo::addRepo(Melodie& m)
{
	melodii.push_back(m);
	savetoFile();
}

void Repo::stergeRepo(int id)
{
	erase_if(melodii, [&](Melodie& m) {
		return m.getId() == id;
		});

}

