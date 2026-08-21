#include "Service.h"

#include <algorithm>

vector<Produs> Service::getSortatPret()
{
    auto rez = repo.getAll();
    sort(rez.begin(), rez.end(), [](Produs& a, Produs& b) {
        return a.getPret() < b.getPret();
        });

    return rez;
}

void Service::adauga(int id, string nume, string tip, double pret)
{
    val.validate(nume, pret);
    repo.addRepo(id, nume, tip, pret);
}

map<string, int> Service::getRaportTip() const
{
    map<string, int> raport;
    auto all = repo.getAll();
    for (const auto& p : all) {
        raport[p.getTip()]++;
    }

    return raport;
}
