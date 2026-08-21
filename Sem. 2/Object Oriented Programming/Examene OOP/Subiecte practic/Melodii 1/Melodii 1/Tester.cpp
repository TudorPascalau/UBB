#include "Tester.h"

#include "Melodie.h"
#include "Repo.h"
#include "Service.h"

#include <cassert>
#include <fstream>
using std::ofstream;

void Tester::testMelodie() {
	Melodie m{ 1,"Cant Stop","RHCP", 2 };
	assert(m.getId() == 1);
	assert(m.getTitlu() == "Cant Stop");
	assert(m.getArtist() == "RHCP");
	assert(m.getRank() == 2);

	m.setRank(3);
	assert(m.getRank() == 3);
	m.setTitlu("Californication");
	assert(m.getTitlu() == "Californication");

}

void Tester::testRepo() {

	ofstream fout("testRepo.txt");
	fout << "1,Cant Stop,RHCP,1";
	fout.close();

	Repo repo{ "testRepo.txt" };
	auto all = repo.getAll();
	assert(all.size() == 1);
	assert(all[0].getRank() == 1);
	assert(all[0].getTitlu() == "Cant Stop");

	repo.modificaMelodie(1, "Californication", 3);
	
	Repo repo2{ "testRepo.txt" };
	all = repo2.getAll();
	assert(all[0].getRank() == 3);
	assert(all[0].getTitlu() == "Californication");

	try {
		repo.modificaMelodie(1, "", 20);
		assert(false);
	}
	catch (RepoException& e) {
		string expected = "Rank invalid";
		assert(e.what() == expected);
	}

	try {
		repo.modificaMelodie(100, "", 5);
		assert(false);
	}
	catch (RepoException& e) {
		string expected = "Nu exista melodie cu id dat";
		assert(e.what() == expected);
	}

	repo.stergeMelodie(1);
	all = repo.getAll();
	assert(all.size() == 0);

	Repo repo3{ "testRepo.txt" };
	all = repo3.getAll();
	assert(all.size() == 0);

}

void Tester::testService() {
	Repo repo{ "testService.txt" };
	Service srv{ repo };

	auto sortat = srv.getSortRank();
	assert(sortat[0].getRank() == 1);
	assert(sortat[3].getRank() == 1);
	assert(sortat[4].getRank() == 2);

	try {
		srv.sterge(10);
		assert(false);
	}
	catch (RepoException& e) {
		string expected = "Ultima melodie de la artist";
		assert(e.what() == expected);
	}
}