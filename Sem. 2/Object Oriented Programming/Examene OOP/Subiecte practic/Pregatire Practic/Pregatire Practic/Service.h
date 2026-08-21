// === Service.h ===
#pragma once
#include "Repo.h"
#include "Validator.h"

#include <algorithm>
#include <vector>
using std::vector;

class Service {
    Repo& repo;
    Validator& validator;

public:
    Service(Repo& repo, Validator& validator)
        : repo{ repo }, validator{ validator } {
    }

    vector<Produs> getAll() const {
        return repo.getAll(); // copie utila pentru sort/filter fara modificarea repo-ului
    }

    void adauga(int id, const string& nume, const string& tip, double pret) {
        Produs e{ id, nume, tip, pret };
        validator.validate(e);
        repo.store(e);
    }

    void modifica(int id, const string& nume, const string& tip, double pret) {
        Produs e{ id, nume, tip, pret };
        validator.validate(e);
        repo.update(e);
    }

    void sterge(int id) {
        repo.remove(id);
    }

    const Produs& cauta(int id) const {
        return repo.find(id);
    }

    vector<Produs> sortatDupaTip() const {
        auto rez = getAll();
        std::sort(rez.begin(), rez.end(), [](const Produs& a, const Produs& b) {
            return a.getTip() < b.getTip();
            });
        return rez;
    }
};
