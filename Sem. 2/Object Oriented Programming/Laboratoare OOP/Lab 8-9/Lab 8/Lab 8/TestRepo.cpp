#include <cassert>

#include "TestRepo.h"


static void test_add_repo() {
	Repo rep;
	Carte c{1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte rez{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };

	assert(rep.repoSize() == 0);

	rep.addCarte(c);
	assert(true);


	assert(rep.repoSize() == 1);
	assert(rep.getById(1) == c);

	try {
		rep.addCarte(c);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Exista deja") != string::npos);
	}

	assert(rep.repoSize() == 1);
	
}

static void test_delete_repo() {
	Repo rep;
	Carte c{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };

	try {
		rep.deleteCarte(0);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}

	rep.addCarte(c);
	assert(rep.repoSize() == 1);

	rep.deleteCarte(1);
	assert(true);

	assert(rep.repoSize() == 0);

	try {
		rep.deleteCarte(1);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}
}

static void test_update_repo() {
	Repo rep;
	Carte c1{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 1, "Ion", "Liviu Rebreanu", "Roman realist", 1920 };
	Carte c3{ 2, "Ion", "Liviu Rebreanu", "Roman realist", 1920 };

	rep.addCarte(c1);


	rep.updateCarte(c2);
	assert(true);


	assert(rep.getById(1) == c2);

	try {
		rep.updateCarte(c3);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}
}

static void test_get_by_id_repo() {
	Repo rep;
	Carte c{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };

	rep.addCarte(c);

	const Carte& rez = rep.getById(1);
	assert(rez == c);

	try {
		rep.getById(99);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}
}

static void test_get_all_repo() {
	Repo rep;
	Carte c1{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 2, "Ion", "Liviu Rebreanu", "Roman realist", 1920 };

	rep.addCarte(c1);
	rep.addCarte(c2);

	const Lista<Carte>& carti = rep.getAll();
	assert(carti.size() == 2);
	assert(carti.getElem(0) == c1);
	assert(carti.getElem(1) == c2);
}

void TestRepo::test_all_repo() const {
	test_add_repo();
	test_delete_repo();
	test_update_repo();
	test_get_by_id_repo();
	test_get_all_repo();
}