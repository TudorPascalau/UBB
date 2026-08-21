#include "Repo.h"

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::stringstream;

void Repo::loadFromFile()
{
	ifstream fin(filename);

	if (!fin.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!");
	}

	string line;
	while (std::getline(fin, line))
	{
		stringstream ss(line);
		string idStr, titlu, autor, pretStr;
		std::getline(ss, idStr, ';');
		std::getline(ss, titlu, ';');
		std::getline(ss, autor, ';');
		std::getline(ss, pretStr, ';');

		int id = std::stoi(idStr);
		int pret = std::stoi(pretStr);

		carti.emplace_back(id, titlu, autor, pret);
	}
	fin.close();
}

void Repo::saveToFile()
{
	ofstream fout(filename);
	if (!fout.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!");
	}
	for (auto& c : carti) {
		fout << c.getId() << ";" << c.getTitlu() << ";" << c.getAutor() << ";" << c.getPret() << "\n";
	}
	fout.close();
}

void Repo::adauga(const Carte& c)
{
	for (const auto& carte : carti) {
		if (carte.getId() == c.getId()) {
			throw RepoException("Carte cu acest ID exista deja!");
		}
	}
	carti.push_back(c);
	saveToFile();
}

vector<Carte> Repo::getAll() const
{
	return carti;
}