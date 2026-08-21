#include "Tester.h"
#include "Service.h"

#include <cassert>

void Tester::testTask()
{
	Task t{ 1, "T1", vector<string>{"Tudor", "Adi"}, "open" };
	assert(t.getId() == 1);
	assert(t.getDescriere() == "T1");
	assert(t.getProgramatori()[0] == "Tudor");
	assert(t.getProgramatori()[1] == "Adi");
	assert(t.getStare() == "open");

	t.setStare("closed");
	assert(t.getStare() == "closed");
}

void Tester::testRepo()
{
	std::ofstream fout("testRepo.txt");
	fout.close();

	Repo repo{ "testRepo.txt" };

	assert(repo.getAll().size() == 0);
	repo.addRepo(1, "T1", vector<string>{"Tudor", "Adi"}, "open");
	assert(repo.getAll().size() == 1);

	try {
		repo.addRepo(1, "T1", vector<string>{"Tudor", "Adi"}, "open");
		assert(false);
	}
	catch (RepoException& e) {
		assert(true);
	}

	repo.modificaStare(1, "closed");

	Repo repo2{ "testRepo.txt" };
	assert(repo2.getAll().size() == 1);
	assert(repo2.getAll()[0].getStare() == "closed");
}

void Tester::testValidator()
{
	Validator val;
	val.validate(1, "T1", vector<string>{"Tudor", "Adi"}, "open");

	try {
		val.validate(1, "", vector<string>{}, "");
		assert(false);
	}
	catch (ValidatorException& ex) {
		string expected = "Descriere vida! Stare invalida! Numar programatori invalid! ";
		assert(ex.what() == expected);
	}
}

void Tester::testService()
{
	Repo repo{ "testService.txt" };
	Validator val;
	Service srv{ repo, val };

	auto sorted = srv.getSortatStare();
	assert(sorted.size() == 10);
	assert(sorted[0].getStare() == "closed");

	auto filter = srv.filterNume("Tudor");
	assert(filter.size() == 3);
}
