#pragma once

#include <cassert>
#include <fstream>

#include "Service.h"

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
	assert(l.get(0) == c);
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

	assert(rez.get(0) == 0);
	assert(all.get(rez.get(0)).getId() == 1);
	assert(all.get(rez.get(0)).getTitlu() == "Ion");
	assert(all.get(rez.get(0)).getAutor() == "Rebreanu");

	assert(rez.get(1) == 3);
	assert(all.get(rez.get(1)).getId() == 4);
	assert(all.get(rez.get(1)).getTitlu() == "Ion");
	assert(all.get(rez.get(1)).getAutor() == "Popescu");
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

	assert(rez.get(0) == 1);
	assert(all.get(rez.get(0)).getId() == 2);
	assert(all.get(rez.get(0)).getTitlu() == "Baltagul");
	assert(all.get(rez.get(0)).getAn() == 1930);

	assert(rez.get(1) == 5);
	assert(all.get(rez.get(1)).getId() == 6);
	assert(all.get(rez.get(1)).getTitlu() == "Test");
	assert(all.get(rez.get(1)).getAn() == 1930);
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

	assert(all.get(rez.get(0)).getTitlu() == "Baltagul");
	assert(all.get(rez.get(1)).getTitlu() == "Enigma Otiliei");
	assert(all.get(rez.get(2)).getTitlu() == "Ion");
	assert(all.get(rez.get(3)).getTitlu() == "Ion");
	assert(all.get(rez.get(4)).getTitlu() == "Morometii");
	assert(all.get(rez.get(5)).getTitlu() == "Test");
}

static void test_sort_by_autor() {
	Service srv = createSrvWithData();
	const Lista<Carte>& all = srv.getAll();

	Lista<int> rez = srv.sortByAutor();

	assert(rez.size() == 6);

	assert(all.get(rez.get(0)).getAutor() == "AutorX");
	assert(all.get(rez.get(1)).getAutor() == "Calinescu");
	assert(all.get(rez.get(2)).getAutor() == "Popescu");
	assert(all.get(rez.get(3)).getAutor() == "Preda");
	assert(all.get(rez.get(4)).getAutor() == "Rebreanu");
	assert(all.get(rez.get(5)).getAutor() == "Sadoveanu");
}

static void test_sort_by_an_gen() {
	Service srv = createSrvWithData();
	const Lista<Carte>& all = srv.getAll();

	Lista<int> rez = srv.sortByAnGen();

	assert(rez.size() == 6);

	assert(all.get(rez.get(0)).getAn() == 1920);
	assert(all.get(rez.get(0)).getGen() == "roman");
	assert(all.get(rez.get(0)).getTitlu() == "Ion");

	assert(all.get(rez.get(1)).getAn() == 1930);
	assert(all.get(rez.get(1)).getGen() == "poezie");
	assert(all.get(rez.get(1)).getTitlu() == "Test");
	assert(all.get(rez.get(2)).getAn() == 1930);
	assert(all.get(rez.get(2)).getGen() == "roman");
	assert(all.get(rez.get(2)).getTitlu() == "Baltagul");

	assert(all.get(rez.get(3)).getAn() == 1938);
	assert(all.get(rez.get(3)).getGen() == "roman");
	assert(all.get(rez.get(3)).getTitlu() == "Enigma Otiliei");
	assert(all.get(rez.get(4)).getAn() == 1955);
	assert(all.get(rez.get(4)).getGen() == "roman");
	assert(all.get(rez.get(4)).getTitlu() == "Morometii");

	assert(all.get(rez.get(5)).getAn() == 2000);
	assert(all.get(rez.get(5)).getGen() == "drama");
	assert(all.get(rez.get(5)).getTitlu() == "Ion");
}

static void test_sort_does_not_modify_repo() {
	Service srv = createSrvWithData();

	Lista<int> rez = srv.sortByTitlu();
	(void)rez;

	const Lista<Carte>& all = srv.getAll();
	assert(all.size() == 6);

	assert(all.get(0).getId() == 1);
	assert(all.get(0).getTitlu() == "Ion");

	assert(all.get(1).getId() == 2);
	assert(all.get(1).getTitlu() == "Baltagul");	
	assert(all.get(2).getId() == 3);
	assert(all.get(2).getTitlu() == "Morometii");

	assert(all.get(3).getId() == 4);
	assert(all.get(3).getTitlu() == "Ion");
	assert(all.get(4).getId() == 5);
	assert(all.get(4).getTitlu() == "Enigma Otiliei");

	assert(all.get(5).getId() == 6);
	assert(all.get(5).getTitlu() == "Test");
}

static void test_filter_does_not_modify_repo() {
	Service srv = createSrvWithData();

	Lista<int> rez = srv.filterByAn(1930);
	(void)rez;

	const Lista<Carte>& all = srv.getAll();
	assert(all.size() == 6);

	assert(all.get(0).getId() == 1);
	assert(all.get(1).getId() == 2);
	assert(all.get(2).getId() == 3);
	assert(all.get(3).getId() == 4);
	assert(all.get(4).getId() == 5);
	assert(all.get(5).getId() == 6);
}

/////////////////////////////////////////////////
//// Aici incep testele pentru cos

static void test_service_adauga_cos_dupa_titlu() {
	Service srv;

	assert(srv.sizeCos() == 0);
	assert(srv.getCos().size() == 0);

	srv.addCarte(1, "Ion", "Liviu Rebreanu", "roman", 1920);
	srv.addCarte(2, "Baltagul", "Mihail Sadoveanu", "roman", 1930);

	srv.adaugaCos("Ion");

	assert(srv.sizeCos() == 1);
	assert(srv.getCos().size() == 1);
	assert(srv.getCos().get(0) == 1);
}

static void test_service_adauga_cos_repetat() {
	Service srv;
	srv.addCarte(1, "Ion", "Liviu Rebreanu", "roman", 1920);

	srv.adaugaCos("Ion");
	srv.adaugaCos("Ion");

	assert(srv.sizeCos() == 2);
	assert(srv.getCos().get(0) == 1);
	assert(srv.getCos().get(1) == 1);
}

static void test_service_adauga_cos_titlu_inexistent() {
	Service srv;
	srv.addCarte(1, "Ion", "Liviu Rebreanu", "roman", 1920);

	try {
		srv.adaugaCos("Morometii");
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage() == "Nu exista carte cu acest titlu\n");
	}
}

static void test_service_goleste_cos() {
	Service srv;
	srv.addCarte(1, "Ion", "Liviu Rebreanu", "roman", 1920);
	srv.addCarte(2, "Baltagul", "Mihail Sadoveanu", "roman", 1930);

	srv.adaugaCos("Ion");
	srv.adaugaCos("Baltagul");
	assert(srv.sizeCos() == 2);

	srv.golesteCos();

	assert(srv.sizeCos() == 0);
	assert(srv.getCos().size() == 0);
}

static void test_service_genereaza_cos() {
	Service srv;

	srv.genereazaCos(5);
	assert(srv.sizeCos() == 0);
	assert(srv.getCos().size() == 0);

	srv.addCarte(10, "Ion", "Liviu Rebreanu", "roman", 1920);
	srv.addCarte(20, "Baltagul", "Mihail Sadoveanu", "roman", 1930);
	srv.addCarte(30, "Enigma Otiliei", "George Calinescu", "roman", 1938);

	srv.genereazaCos(2);

	assert(srv.sizeCos() == 2);
	assert(srv.getCos().size() == 2);

	try {
		srv.genereazaCos(4);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage() == "Nu exista suficiente carti pentru generarea cosului.\n");
	}
}

static void test_service_delete_carte_actualizeaza_cos() {
	Service srv;

	srv.addCarte(1, "Ion", "Liviu Rebreanu", "roman", 1920);
	srv.addCarte(2, "Baltagul", "Mihail Sadoveanu", "roman", 1930);

	srv.adaugaCos("Ion");
	srv.adaugaCos("Baltagul");
	srv.adaugaCos("Ion");

	assert(srv.sizeCos() == 3);

	srv.deleteCarte(1);

	assert(srv.sizeCos() == 1);
	assert(srv.getCos().get(0) == 2);
}

static void test_service_export_cos_csv() {
	Service srv;
	srv.addCarte(1, "Ion", "Liviu Rebreanu", "roman", 1920);
	srv.addCarte(2, "Baltagul", "Mihail Sadoveanu", "roman", 1930);

	srv.adaugaCos("Ion");
	srv.adaugaCos("Baltagul");

	srv.exportCosCSV("test_cos.csv");

	std::ifstream fin("test_cos.csv");
	assert(fin.is_open());

	string continut;
	string linie;
	while (getline(fin, linie)) {
		continut += linie;
		continut += '\n';
	}
	fin.close();

	assert(continut.find("id,titlu,autor,gen,an") != string::npos);
	assert(continut.find("Ion") != string::npos);
	assert(continut.find("Baltagul") != string::npos);

	std::remove("test_cos.csv");
}

static void test_service_raport() {
	Service srv;
	srv.addCarte(1, "Ion", "Liviu Rebreanu", "roman", 1920);
	srv.addCarte(2, "Baltagul", "Mihail Sadoveanu", "roman", 1930);

	auto raport = srv.raportGen();
	assert(raport.size() == 1);
	assert(raport.get(0).getGen() == "roman");
	assert(raport.get(0).getCount() == 2);
}

static void test_service_undo() {
	Service srv;

	try {
		srv.undo();
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("undo") != string::npos);
	}

	srv.addCarte(1, "Ion", "Liviu Rebreanu", "roman", 1920);
	assert(srv.getAll().size() == 1);
	srv.undo();
	assert(srv.getAll().size() == 0);

	srv.addCarte(2, "Baltagul", "Mihail Sadoveanu", "roman", 1930);
	srv.deleteCarte(2);
	assert(srv.getAll().size() == 0);
	srv.undo();
	assert(srv.getAll().size() == 1);
	assert(srv.findCarte(2).getTitlu() == "Baltagul");

	srv.updateCarte(2, "Baltagul nou", "Autor nou", "drama", 2000);
	assert(srv.findCarte(2).getTitlu() == "Baltagul nou");
	srv.undo();
	const Carte& c = srv.findCarte(2);
	assert(c.getTitlu() == "Baltagul");
	assert(c.getAutor() == "Mihail Sadoveanu");
	assert(c.getGen() == "roman");
	assert(c.getAn() == 1930);
}

void test_all_service() {
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

	test_service_adauga_cos_dupa_titlu();
	test_service_adauga_cos_titlu_inexistent();
	test_service_adauga_cos_repetat();
	test_service_goleste_cos();
	test_service_genereaza_cos();
	test_service_delete_carte_actualizeaza_cos();
	test_service_export_cos_csv();

	test_service_raport();
	test_service_undo();
}
