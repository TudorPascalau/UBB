#include "Service.h"

#include <algorithm>

vector<Articol> Service::filterByBrand(const string& brand) {
    vector<Articol> filtered;
    for (const auto& a : repo.getAll()) {
        if (a.getBrand() == brand) {
            filtered.push_back(a);
        }
    }
    return filtered;
}

vector<Articol> Service::sortByMarime() {
    vector<Articol> sorted = repo.getAll();
    std::sort(sorted.begin(), sorted.end(), [](const Articol& a, const Articol& b) {
        return a.getMarime() < b.getMarime();
    });
    return sorted;
}