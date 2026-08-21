#include "Service.h"

#include <algorithm>

vector<XO> Service::getSortatStare() const
{
    auto rez = repo.getAll();
    sort(rez.begin(), rez.end(), [&](XO& a, XO& b) {
        return a.getStare() < b.getStare();
        });

    return rez;
}

void Service::adauga(int dim, string table, string player)
{
    val.validate(dim, table, player, "Neinceput");

    int idMax = 0;
    const auto& all = repo.getAll();
    for (const auto& j : all) {
        if (j.getId() > idMax) {
            idMax = j.getId();
        }
    }
    idMax++;

    repo.addRepo(idMax, dim, table, player, "Neinceput");
}

void Service::modifica(int id, int dim, string table, string player, string stare)
{
    val.validate(dim, table, player, stare);
    repo.modificaRepo(id, dim, table, player, stare);
}

XO Service::getJocById(int id)
{
    auto all = repo.getAll();
    for (auto& j : all) {
        if (j.getId() == id) {
            XO joc = j;
            return joc;
        }
    }

    throw(RepoException("Nu exista joc cu id dat! "));
}
