#include "Repo.h"

#include <fstream>
#include <sstream>

void Repo::loadFromFile(const string& filename) {
	std::ifstream in(filename);
	if (!in.is_open()) {
		throw RepoError("Error opening file");
	}

	string line;
	while (std::getline(in, line)) {
		if (line.empty()) {
			continue;
		}

		std::stringstream ss(line);
		string codStr, denumire, marime, pretStr, disponibilStr;

		std::getline(ss, codStr, ',');
		std::getline(ss, denumire, ',');
		std::getline(ss, marime, ',');
		std::getline(ss, pretStr, ',');
		std::getline(ss, disponibilStr, ',');

		int cod = std::stoi(codStr);
		int pret = std::stoi(pretStr);
		bool disponibil = (disponibilStr == "true");

		Rochie rochie(cod, denumire, marime, pret, disponibil);
		addRochie(rochie);
	}

}

void Repo::saveToFile(const string& filename) {
	std::ofstream out(filename);
	if(!out.is_open()) {
		throw RepoError("Error opening file");
	}

	for(const auto& rochie : rochii) {
		out << rochie.getCod() << ","
			<< rochie.getDenumire() << ","
			<< rochie.getMarime() << ","
			<< rochie.getPret() << ","
			<< (rochie.getDisponibil() ? "true" : "false") << "\n";
	}
}

void Repo::addRochie(const Rochie& rochie) {
	int cod = rochie.getCod();
	for (auto& r : rochii) {
		if (r.getCod() == cod) {
			throw RepoError("Cod deja existent!");
		}
	}

	rochii.push_back(rochie);
	saveToFile(file);
}

void Repo::inchireazaRochie(int cod) {
	for (auto& r : rochii) {
		if (r.getCod() == cod) {
			if (r.getDisponibil() == false) {
				throw RepoError("Rochie indisponibila!");
			}
			else {
				r.setDisponibil(false);
				saveToFile(file);
				return;
			}
		}
	}
}