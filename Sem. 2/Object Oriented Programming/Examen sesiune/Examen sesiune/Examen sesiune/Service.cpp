#include "Service.h"

vector<Task> Service::getSortatStare() const
{
	auto rez = repo.getAll();
	std::sort(rez.begin(), rez.end(), [&](Task& a, Task& b) {
		return a.getStare() < b.getStare();
		});

	return rez;
}

vector<Task> Service::filterNume(const string& nume) const
{
	vector<Task> rez;
	auto sortat = getSortatStare();
	for (const auto& t : sortat) {
		auto prog = t.getProgramatori();
		for (const auto& p : prog) {
			if (p == nume) {
				rez.push_back(t);
				continue;
			}
		}
	}

	return rez;
}

void Service::adauga(int id, const string& descriere, const vector<string>& programatori, const string& stare)
{
	val.validate(id, descriere, programatori, stare);
	repo.addRepo(id, descriere, programatori, stare);
}

