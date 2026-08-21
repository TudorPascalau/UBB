#include "Tester.h"

#include <cassert>

void Tester::testMelodie()
{
	Melodie m{ 1,"Boogie Wonderland", "Earth, Wind and Fire", "disco" };
	assert(m.getId() == 1);
	assert(m.getGen() == "disco");
	assert(m.getArtist() == "Earth, Wind and Fire");
	assert(m.getTitlu() == "Boogie Wonderland");
}

void Tester::testRepo() 
{
	ofstream fout("testRepo.txt");
	fout.close();

	Repo repo{ "testRepo.txt" };
	auto all = repo.getAll();
	assert(all.size() == 0);

	Melodie m{ 1,"Boogie Wonderland", "Earth, Wind and Fire", "disco" };
	repo.addRepo(m);
	
	Repo rep{ "testRepo.txt" };
	all = rep.getAll();
	assert(all.size() == 1);

	rep.stergeRepo(1);
	all = rep.getAll();
	assert(all.size() == 0);
}

void Tester::testService()
{
	Repo repo{ "testService.txt" };
	Service srv{ repo };

	auto sortat = srv.getSortateArtist();
	assert(sortat[0].getArtist() == "AC/DC");

	try {
		srv.adauga("", "", "");
		assert(false);
	}
	catch (RepoException& e) {
		string expected = "Gen invalid";
		assert(e.what() == expected);
	}
}