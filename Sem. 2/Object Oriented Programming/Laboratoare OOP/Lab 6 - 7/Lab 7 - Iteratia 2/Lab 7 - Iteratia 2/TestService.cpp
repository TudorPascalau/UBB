#include <cassert>

#include "TestService.h"

static void test_add_service() {
	Service s;

	try {
		s.addCarte(0, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881);
		assert(false);
	}
	catch (const ValidationError& e) {
		assert(e.getMessage().find("Id invalid") != string::npos);
	}

	s.addCarte(1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881);
	assert(s.getAll().size() == 1);

	try {
		s.addCarte(1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Exista deja") != string::npos);
	}
}

static void test_delete_service() {
	Service s;

	try {
		s.deleteCarte(0);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}

	s.addCarte(1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881);

	s.deleteCarte(1);
	assert(s.getAll().size() == 0);

	try {
		s.deleteCarte(1);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}
}

static void test_update_service() {
	Service s;

	s.addCarte(1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881);

	try {
		s.updateCarte(2, "Ion", "Liviu Rebreanu", "Roman realist", 1920);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}

	try {
		s.updateCarte(1, "", "Liviu Rebreanu", "Roman realist", 1920);
		assert(false);
	}
	catch (const ValidationError& e) {
		assert(e.getMessage().find("Titlu invalid") != string::npos);
	}

	s.updateCarte(1, "Ion", "Liviu Rebreanu", "Roman realist", 1920);

	const Carte& rez = s.findCarte(1);
	assert(rez.getTitlu() == "Ion");
	assert(rez.getAutor() == "Liviu Rebreanu");
	assert(rez.getGen() == "Roman realist");
	assert(rez.getAn() == 1920);
}

static void test_find_service() {
	Service s;

	s.addCarte(1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881);

	const Carte& rez = s.findCarte(1);
	assert(rez.getTitlu() == "Moara cu noroc");

	try {
		s.findCarte(0);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}
}

static void test_get_all_service() {
	Service s;
	Carte c{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };

	s.addCarte(1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881);

	const Lista<Carte>& l = s.getAll();
	assert(l.size() == 1);
	assert(l.getElem(0) == c);
}

//////////////////////////////////////////
// Aici incep testele pentru filtrari si sortari cu indici

static Service createSrvWithData() {
	Service srv;

	srv.addCarte(1, "Ion", "Rebreanu", "roman", 1920);
	srv.addCarte(2, "Baltagul", "Sadoveanu", "roman", 1930);
	srv.addCarte(3, "Morometii", "Preda", "roman", 1955);
	srv.addCarte(4, "Ion", "Popescu", "drama", 2000);
	srv.addCarte(5, "Enigma Otiliei", "Calinescu", "roman", 1938);
	srv.addCarte(6, "Test", "AutorX", "poezie", 1930);

	return srv;
}

static void test_filter_by_titlu() {
	Service srv = createSrvWithData();
	const Lista<Carte>& all = srv.getAll();

	Lista<int> rez = srv.filterByTitlu("Ion");

	assert(rez.size() == 2);

	assert(rez.getElem(0) == 0);
	assert(all.getElem(rez.getElem(0)).getId() == 1);
	assert(all.getElem(rez.getElem(0)).getTitlu() == "Ion");
	assert(all.getElem(rez.getElem(0)).getAutor() == "Rebreanu");

	assert(rez.getElem(1) == 3);
	assert(all.getElem(rez.getElem(1)).getId() == 4);
	assert(all.getElem(rez.getElem(1)).getTitlu() == "Ion");
	assert(all.getElem(rez.getElem(1)).getAutor() == "Popescu");
}

static void test_filter_by_titlu_no_result() {
	Service srv = createSrvWithData();

	Lista<int> rez = srv.filterByTitlu("Carte inexistenta");

	assert(rez.size() == 0);
}

static void test_filter_by_an() {
	Service srv = createSrvWithData();
	const Lista<Carte>& all = srv.getAll();

	Lista<int> rez = srv.filterByAn(1930);

	assert(rez.size() == 2);

	assert(rez.getElem(0) == 1);
	assert(all.getElem(rez.getElem(0)).getId() == 2);
	assert(all.getElem(rez.getElem(0)).getTitlu() == "Baltagul");
	assert(all.getElem(rez.getElem(0)).getAn() == 1930);

	assert(rez.getElem(1) == 5);
	assert(all.getElem(rez.getElem(1)).getId() == 6);
	assert(all.getElem(rez.getElem(1)).getTitlu() == "Test");
	assert(all.getElem(rez.getElem(1)).getAn() == 1930);
}

static void test_filter_by_an_no_result() {
	Service srv = createSrvWithData();

	Lista<int> rez = srv.filterByAn(1111);

	assert(rez.size() == 0);
}

static void test_sort_by_titlu() {
	Service srv = createSrvWithData();
	const Lista<Carte>& all = srv.getAll();

	Lista<int> rez = srv.sortByTitlu();

	assert(rez.size() == 6);

	assert(all.getElem(rez.getElem(0)).getTitlu() == "Baltagul");
	assert(all.getElem(rez.getElem(1)).getTitlu() == "Enigma Otiliei");
	assert(all.getElem(rez.getElem(2)).getTitlu() == "Ion");
	assert(all.getElem(rez.getElem(3)).getTitlu() == "Ion");
	assert(all.getElem(rez.getElem(4)).getTitlu() == "Morometii");
	assert(all.getElem(rez.getElem(5)).getTitlu() == "Test");
}

static void test_sort_by_autor() {
	Service srv = createSrvWithData();
	const Lista<Carte>& all = srv.getAll();

	Lista<int> rez = srv.sortByAutor();

	assert(rez.size() == 6);

	assert(all.getElem(rez.getElem(0)).getAutor() == "AutorX");
	assert(all.getElem(rez.getElem(1)).getAutor() == "Calinescu");
	assert(all.getElem(rez.getElem(2)).getAutor() == "Popescu");
	assert(all.getElem(rez.getElem(3)).getAutor() == "Preda");
	assert(all.getElem(rez.getElem(4)).getAutor() == "Rebreanu");
	assert(all.getElem(rez.getElem(5)).getAutor() == "Sadoveanu");
}

static void test_sort_by_an_gen() {
	Service srv = createSrvWithData();
	const Lista<Carte>& all = srv.getAll();

	Lista<int> rez = srv.sortByAnGen();

	assert(rez.size() == 6);

	assert(all.getElem(rez.getElem(0)).getAn() == 1920);
	assert(all.getElem(rez.getElem(0)).getGen() == "roman");
	assert(all.getElem(rez.getElem(0)).getTitlu() == "Ion");

	assert(all.getElem(rez.getElem(1)).getAn() == 1930);
	assert(all.getElem(rez.getElem(1)).getGen() == "poezie");
	assert(all.getElem(rez.getElem(1)).getTitlu() == "Test");

	assert(all.getElem(rez.getElem(2)).getAn() == 1930);
	assert(all.getElem(rez.getElem(2)).getGen() == "roman");
	assert(all.getElem(rez.getElem(2)).getTitlu() == "Baltagul");

	assert(all.getElem(rez.getElem(3)).getAn() == 1938);
	assert(all.getElem(rez.getElem(3)).getGen() == "roman");
	assert(all.getElem(rez.getElem(3)).getTitlu() == "Enigma Otiliei");

	assert(all.getElem(rez.getElem(4)).getAn() == 1955);
	assert(all.getElem(rez.getElem(4)).getGen() == "roman");
	assert(all.getElem(rez.getElem(4)).getTitlu() == "Morometii");

	assert(all.getElem(rez.getElem(5)).getAn() == 2000);
	assert(all.getElem(rez.getElem(5)).getGen() == "drama");
	assert(all.getElem(rez.getElem(5)).getTitlu() == "Ion");
}

static void test_sort_does_not_modify_repo() {
	Service srv = createSrvWithData();

	Lista<int> rez = srv.sortByTitlu();
	(void)rez;

	const Lista<Carte>& all = srv.getAll();
	assert(all.size() == 6);

	assert(all.getElem(0).getId() == 1);
	assert(all.getElem(0).getTitlu() == "Ion");

	assert(all.getElem(1).getId() == 2);
	assert(all.getElem(1).getTitlu() == "Baltagul");

	assert(all.getElem(2).getId() == 3);
	assert(all.getElem(2).getTitlu() == "Morometii");

	assert(all.getElem(3).getId() == 4);
	assert(all.getElem(3).getTitlu() == "Ion");

	assert(all.getElem(4).getId() == 5);
	assert(all.getElem(4).getTitlu() == "Enigma Otiliei");

	assert(all.getElem(5).getId() == 6);
	assert(all.getElem(5).getTitlu() == "Test");
}

static void test_filter_does_not_modify_repo() {
	Service srv = createSrvWithData();

	Lista<int> rez = srv.filterByAn(1930);
	(void)rez;

	const Lista<Carte>& all = srv.getAll();
	assert(all.size() == 6);

	assert(all.getElem(0).getId() == 1);
	assert(all.getElem(1).getId() == 2);
	assert(all.getElem(2).getId() == 3);
	assert(all.getElem(3).getId() == 4);
	assert(all.getElem(4).getId() == 5);
	assert(all.getElem(5).getId() == 6);
}

void TestService::test_all_service() const {
	test_add_service();
	test_delete_service();
	test_update_service();
	test_find_service();
	test_get_all_service();

	test_filter_by_titlu();
	test_filter_by_titlu_no_result();
	test_filter_by_an();
	test_filter_by_an_no_result();

	test_sort_by_titlu();
	test_sort_by_autor();
	test_sort_by_an_gen();

	test_sort_does_not_modify_repo();
	test_filter_does_not_modify_repo();
}