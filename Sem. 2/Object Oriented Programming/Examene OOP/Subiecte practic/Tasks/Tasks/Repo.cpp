#include "Repo.h"

void Repo::loadFile()
{
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		throw(RepoException("Error opening file"));
	}

	string line;
	while (getline(fin, line)) {
		std::stringstream ss(line);
		string idStr, descriere, p, stare;

		getline(ss, idStr, ';');
		getline(ss, descriere, ';');
		getline(ss, p, ';');
		getline(ss, stare, ';');

		int id = stoi(idStr);
		vector<string> programatori;
		std::stringstream pstream(p);
		string programator;
		while (getline(pstream, programator, ',')) {
			programatori.push_back(programator);
		}

		tasks.emplace_back(id, descriere, programatori, stare);
	}

	fin.close();
}

void Repo::saveToFile()
{
	std::ofstream fout(filename);
	if (!fout.is_open()) {
		throw(RepoException("Error opening file"));
	}

	for (const auto& t : tasks) {
		fout << t.getId() << ';' << t.getDescriere() << ';';
		auto prog = t.getProgramatori();
		int n = prog.size();
		for (int i = 0; i < n - 1; i++) {
			fout << prog[i] << ',';
		}
		fout << prog[n - 1] << ';';
		fout << t.getStare() << '\n';
	}

	fout.close();
}

void Repo::addRepo(int id, const string& descriere, const vector<string>& programatori, const string& stare)
{
	for (const auto& t : tasks) {
		if (t.getId() == id) {
			throw(RepoException("Id deja existent! "));
		}
	}

	tasks.emplace_back(id, descriere, programatori, stare);
	saveToFile();
}

void Repo::modificaStare(int id, const string& newStare)
{
	for (auto& t : tasks) {
		if (t.getId() == id) {
			t.setStare(newStare);
			break;
		}
	}
}
