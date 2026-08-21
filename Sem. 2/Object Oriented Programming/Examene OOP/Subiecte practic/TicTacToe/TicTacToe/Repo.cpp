#include "Repo.h"

void Repo::loadFile()
{
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		throw(RepoException("File open error"));
	}

	string line;
	while (getline(fin, line)) {
		if (line.empty()) {
			continue;
		}

		string idStr, dimStr, table, player, stare;
		std::stringstream ss(line);

		getline(ss, idStr, ',');
		getline(ss, dimStr, ',');
		getline(ss, table, ',');
		getline(ss, player, ',');
		getline(ss, stare, ',');

		int id = stoi(idStr);
		int dim = stoi(dimStr);

		jocuri.emplace_back(id, dim, table, player, stare);
	}

	fin.close();
}

void Repo::saveToFile()
{
	std::ofstream fout(filename);
	if (!fout.is_open()) {
		throw(RepoException("Error opening file"));
	}

	for (const auto& j : jocuri) {
		fout << j.getId() << ',' << j.getDim() << ',' << j.getTabla() << ',' 
			<< j.getPlayer() << ',' << j.getStare() << '\n';
	}
	fout.close();
}

void Repo::modificaRepo(int id, int dim, string table, string player, string stare)
{
	for (auto& j : jocuri) {
		if (j.getId() == id) {
			j.setDim(dim);
			j.setTabla(table);
			j.setPlayer(player);
			j.setStare(stare);
			break;
		}
	}
	saveToFile();
}
