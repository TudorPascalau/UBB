#include "Tester.h"

#include "Tractor.h"
#include "Repo.h"
#include "Validator.h"
#include "Service.h"

#include <cassert>
#include <fstream>
using std::ofstream;

void Tester::testTractor() const {
	Tractor t{ 1, "Tractor1", "Tip1", 4 };
	assert(t.getId() == 1);
	assert(t.getDenumire() == "Tractor1");
	assert(t.getTip() == "Tip1");
	assert(t.getNrRoti() == 4);
}

void Tester::testRepo() const {

	ofstream fout("testRepo.txt");
	fout.close();

	Repo repo{ "testRepo.txt" };
	Tractor t{ 1,"John Deere", "agricultura", 4 };
	repo.addRepo(t);

	try {
		repo.addRepo(t);
		assert(false);
	}
	catch (RepoException& e) {
		string expected = "Exista tractor cu acelasi id!";
		assert(e.what() == expected);
	}
}

void Tester::testValidator() const {
	Validator validator;

	try {
		validator.validate(1, "Tractor1", "Tip1", 4);
		assert(true);
	}
	catch (const ValidatorException& e) {
		assert(false);
	}

	try {
		validator.validate(-1, "", "", 3);
		assert(false);
	}
	catch (const ValidatorException& e) {
		string expected = "ID invalid! Denumire invalida! Tip invalid! Numar de roti invalid! ";
		assert(e.what() == expected);
	}
}

void Tester::testService() const {
	Repo repo{ "testService.txt" };
	Validator val;
	Service service{ repo, val };

	assert(service.nrTractoare() == 6);

	auto sorted = service.getSortatDenumire();
	assert(sorted.size() == 6);
	assert(sorted[0].getDenumire() == "Case IH");

}