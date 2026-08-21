#pragma once

#include <map>
#include <random>

#include "AbstractRepo.h"

class RepoDict : public RepoAbstract
{
private:
	std::map<int, Carte> carti;
	Lista<Carte> allCarti;
	double probabilitate;
	mutable std::mt19937 randomGenerator;

	void refreshAll();
	void maybeThrow() const;

public:
	explicit RepoDict(double probabilitate = 0.0);

	int repoSize() const override;

	void addCarte(const Carte& c) override;

	void deleteCarte(int id) override;

	void updateCarte(const Carte& c) override;

	const Carte& getById(int id) const override;

	const Lista<Carte>& getAll() const override;
};
