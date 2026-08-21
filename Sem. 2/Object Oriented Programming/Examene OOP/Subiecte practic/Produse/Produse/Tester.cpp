#include "Tester.h"

#include <cassert>
#include <fstream>

void Tester::testProdus() {
	Produs p{ 1,"Laptop Gaming ASUS","Electronice",49.99 };
	assert(p.getId() == 1);
	assert(p.getPret() == 49.99);
}

void Tester::testRepo()
{
	std::ofstream fout("testRepo.txt");
	fout.close();

	Repo repo{ "testRepo.txt" };
	auto all = repo.getAll();

	repo.addRepo(1, "Laptop Gaming ASUS", "Electronice", 49.99);
	try {
		repo.addRepo(1, "Laptop Gaming ASUS", "Electronice", 49.99);
		assert(false);
	}
	catch(RepoException& e) {
		string expected = "Id deja existent! ";
		assert(e.what() == expected);
	}
}

void Tester::testValidator()
{
	Validator val;
	try {
		val.validate("", 0.0);
		assert(false);
	}
	catch (ValidatorException& e) {
		string expected = "Nume invalid! Pret invalid! ";
		assert(e.what() == expected);
	}
}

void Tester::testService()
{
	Repo repo{ "testService.txt" };
	Validator val;
	Service srv{ repo, val };

	auto sortat = srv.getSortatPret();
	assert(sortat[0].getPret() == 12.75);

	auto raport = srv.getRaportTip();
	assert(raport["Electronice"] == 5);
}
