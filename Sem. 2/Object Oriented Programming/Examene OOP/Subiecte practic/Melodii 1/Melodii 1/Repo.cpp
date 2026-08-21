#include "Repo.h"

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <sstream>
using std::stringstream;

#include <algorithm>


const vector<Melodie>& Repo::getAll() const
{
	return melodii;
}

void Repo::modificaMelodie(int id, string titlu, int rank)
{
	if (rank < 0 || rank > 10) {
		throw(RepoException("Rank invalid"));
	}

	for (auto& m : melodii) {
		if (m.getId() == id) {
			m.setRank(rank);
			m.setTitlu(titlu);
			saveToFile();
			return;
		}
	}

	throw RepoException("Nu exista melodie cu id dat");
}

void Repo::stergeMelodie(int id)
{
	erase_if(melodii, [&](const Melodie& m) {
		return m.getId() == id;
		});

	saveToFile();
}

void Repo::loadFile()
{
	ifstream fin(fileName);
	if (!fin.is_open()) {
		throw RepoException("File couldnt open!");
	}

	string line;
	while (getline(fin, line)) {

		if (line.empty()) {
			continue;
		}

		stringstream ss(line);
		string idStr, titlu, artist, rankStr;
		getline(ss, idStr, ',');
		getline(ss, titlu, ',');
		getline(ss, artist, ',');
		getline(ss, rankStr, ',');

		int id = stoi(idStr);
		int rank = stoi(rankStr);

		melodii.emplace_back(id, titlu, artist, rank);
	}

	fin.close();
}

void Repo::saveToFile()
{
	ofstream fout(fileName);

	for (const auto& m : melodii) {
		int id = m.getId();
		string titlu = m.getTitlu();
		string artist = m.getArtist();
		int rank = m.getRank();

		fout << id << ',' << titlu << ',' << artist << ',' << rank << '\n';
	}

	fout.close();
}
