#pragma once

#include <string>
using std::string;

#include "AbstractRepo.h"

class FileRepo : public RepoAbstract
{
private:
	RepoAbstract& repo;
	string fileName;

	void loadFromFile();
	void writeToFile() const;

public:
	FileRepo(RepoAbstract& repo, const string& fileName);

	int repoSize() const override;
	void addCarte(const Carte& c) override;
	void deleteCarte(int id) override;
	void updateCarte(const Carte& c) override;
	const Carte& getById(int id) const override;
	const Lista<Carte>& getAll() const override;
};
