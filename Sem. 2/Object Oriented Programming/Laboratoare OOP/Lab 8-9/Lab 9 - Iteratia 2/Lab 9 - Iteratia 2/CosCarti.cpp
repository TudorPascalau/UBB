#include "CosCarti.h"

#include "Repo.h"

void CosCarti::adauga(int id) {
	idCarti.add(id);
}

void CosCarti::goleste() noexcept {
	idCarti.clear();
}

void CosCarti::stergeId(int id) {
	auto it = std::remove(idCarti.begin(), idCarti.end(), id);
	idCarti.erase(it, idCarti.end());
}

const Lista<int>& CosCarti::getAll() const noexcept {
	return idCarti;
}

int CosCarti::size() const noexcept {
	return idCarti.size();
}