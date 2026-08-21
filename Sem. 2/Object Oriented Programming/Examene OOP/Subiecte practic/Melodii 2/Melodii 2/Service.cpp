#include "Service.h"

#include <algorithm>

vector<Melodie> Service::getSortateArtist()
{
    auto rez = repo.getAll();

    sort(rez.begin(), rez.end(), [](Melodie& a, Melodie& b) {
        return a.getArtist() < b.getArtist();
        });

    return rez;
}

void Service::adauga(string titlu, string artist, string gen)
{
    if (gen != "pop" && gen != "rock" && gen != "folk" && gen != "disco") {
        throw(RepoException("Gen invalid"));
    }

    int max = 0;
    auto mel = repo.getAll();
    for (const auto& m : mel) {
        if (m.getId() > max) {
            max = m.getId();
        }
    }

    int id = max + 1;
    Melodie m{ id, titlu, artist, gen };
    repo.addRepo(m);
}
