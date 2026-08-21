#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

#include "FileRepo.h"
#include "Repo.h"
#include "RepoDict.h"

using std::string;

static void write_file_repo_test_file(const string& fileName, const string& content) {
	std::ofstream out(fileName);
	out << content;
}

static void remove_file_repo_test_file(const string& fileName) {
	std::filesystem::remove(fileName);
}

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
	assert(carti.get(0) == c1);
	assert(carti.get(1) == c2);
}

static void test_file_repo_load_missing_file() {
	const string fileName = "test_file_repo_missing.txt";
	remove_file_repo_test_file(fileName);

	Repo repoMemorie;
	FileRepo rep{ repoMemorie, fileName };
	assert(rep.repoSize() == 0);
}

static void test_file_repo_load_valid_file_and_skip_empty_lines() {
	const string fileName = "test_file_repo_valid.txt";
	write_file_repo_test_file(fileName,
		"\n"
		"1\nMoara cu noroc\nIoan Slavici\nNuvela psihologica\n1881\n"
		"2\nIon\nLiviu Rebreanu\nRoman realist\n1920\n");

	Repo repoMemorie;
	FileRepo rep{ repoMemorie, fileName };
	const Carte c1{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };
	const Carte c2{ 2, "Ion", "Liviu Rebreanu", "Roman realist", 1920 };
	assert(rep.repoSize() == 2);
	assert(rep.getById(1) == c1);
	assert(rep.getById(2) == c2);

	remove_file_repo_test_file(fileName);
}

static void test_file_repo_persists_add_update_delete() {
	const string fileName = "test_file_repo_persist.txt";
	write_file_repo_test_file(fileName, "");

	Repo repoMemorie;
	FileRepo rep{ repoMemorie, fileName };
	const Carte c1{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };
	const Carte c2{ 2, "Ion", "Liviu Rebreanu", "Roman realist", 1920 };
	const Carte c2Update{ 2, "Padurea spanzuratilor", "Liviu Rebreanu", "Roman psihologic", 1922 };

	rep.addCarte(c1);
	rep.addCarte(c2);

	Repo repoAfterAdd;
	FileRepo afterAdd{ repoAfterAdd, fileName };
	assert(afterAdd.repoSize() == 2);
	assert(afterAdd.getById(1) == c1);
	assert(afterAdd.getById(2) == c2);

	rep.updateCarte(c2Update);
	Repo repoAfterUpdate;
	FileRepo afterUpdate{ repoAfterUpdate, fileName };
	assert(afterUpdate.repoSize() == 2);
	assert(afterUpdate.getById(2) == c2Update);

	rep.deleteCarte(1);
	Repo repoAfterDelete;
	FileRepo afterDelete{ repoAfterDelete, fileName };
	assert(afterDelete.repoSize() == 1);
	assert(afterDelete.getById(2) == c2Update);

	remove_file_repo_test_file(fileName);
}

static void test_file_repo_invalid_missing_fields() {
	const string fileName = "test_file_repo_missing_fields.txt";
	write_file_repo_test_file(fileName, "1\nMoara cu noroc\nIoan Slavici\n");

	try {
		Repo repoMemorie;
		FileRepo rep{ repoMemorie, fileName };
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("format valid") != string::npos);
	}

	remove_file_repo_test_file(fileName);
}

static void test_file_repo_invalid_id() {
	const string fileName = "test_file_repo_invalid_id.txt";
	write_file_repo_test_file(fileName, "abc\nMoara cu noroc\nIoan Slavici\nNuvela psihologica\n1881\n");

	try {
		Repo repoMemorie;
		FileRepo rep{ repoMemorie, fileName };
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("format valid") != string::npos);
	}

	remove_file_repo_test_file(fileName);
}

static void test_file_repo_invalid_year() {
	const string fileName = "test_file_repo_invalid_year.txt";
	write_file_repo_test_file(fileName, "1\nMoara cu noroc\nIoan Slavici\nNuvela psihologica\nan\n");

	try {
		Repo repoMemorie;
		FileRepo rep{ repoMemorie, fileName };
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("format valid") != string::npos);
	}

	remove_file_repo_test_file(fileName);
}

static void test_file_repo_write_error() {
	const string dirName = "test_file_repo_dir";
	std::filesystem::create_directory(dirName);

	Repo repoMemorie;
	FileRepo rep{ repoMemorie, dirName };
	try {
		rep.addCarte(Carte{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 });
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("scriere") != string::npos);
	}

	std::filesystem::remove(dirName);
}

static void test_repo_dict_probability_zero() {
	RepoDict rep{ 0 };
	const Carte c{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };

	rep.addCarte(c);
	assert(rep.repoSize() == 1);
	assert(rep.getById(1) == c);
	assert(rep.getAll().size() == 1);

	rep.updateCarte(Carte{ 1, "Ion", "Liviu Rebreanu", "Roman realist", 1920 });
	assert(rep.getById(1).getTitlu() == "Ion");

	rep.deleteCarte(1);
	assert(rep.repoSize() == 0);
}

static void test_repo_dict_add_duplicate() {
	RepoDict rep{ 0 };
	const Carte c{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };

	rep.addCarte(c);
	try {
		rep.addCarte(c);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Exista deja") != string::npos);
	}

	assert(rep.repoSize() == 1);
	assert(rep.getById(1) == c);
}

static void test_repo_dict_delete() {
	RepoDict rep{ 0 };
	const Carte c1{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };
	const Carte c2{ 2, "Ion", "Liviu Rebreanu", "Roman realist", 1920 };

	try {
		rep.deleteCarte(1);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}

	rep.addCarte(c1);
	rep.addCarte(c2);
	rep.deleteCarte(1);

	assert(rep.repoSize() == 1);
	assert(rep.getAll().size() == 1);
	assert(rep.getAll().get(0) == c2);

	try {
		rep.getById(1);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}
}

static void test_repo_dict_update() {
	RepoDict rep{ 0 };
	const Carte c1{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };
	const Carte c1Update{ 1, "Ion", "Liviu Rebreanu", "Roman realist", 1920 };
	const Carte cMissing{ 2, "Padurea spanzuratilor", "Liviu Rebreanu", "Roman psihologic", 1922 };

	rep.addCarte(c1);
	rep.updateCarte(c1Update);

	assert(rep.getById(1) == c1Update);
	assert(rep.getAll().size() == 1);
	assert(rep.getAll().get(0) == c1Update);

	try {
		rep.updateCarte(cMissing);
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Nu exista") != string::npos);
	}
}

static void test_repo_dict_get_all_ordered_by_id() {
	RepoDict rep{ 0 };
	const Carte c3{ 3, "Enigma Otiliei", "George Calinescu", "roman", 1938 };
	const Carte c1{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };
	const Carte c2{ 2, "Ion", "Liviu Rebreanu", "Roman realist", 1920 };

	rep.addCarte(c3);
	rep.addCarte(c1);
	rep.addCarte(c2);

	const Lista<Carte>& all = rep.getAll();
	assert(all.size() == 3);
	assert(all.get(0) == c1);
	assert(all.get(1) == c2);
	assert(all.get(2) == c3);
}

static void test_repo_dict_accepts_decimal_probabilities() {
	RepoDict rep25{ 0.25 };
	RepoDict rep50{ 0.5 };
	RepoDict rep75{ 0.75 };

	assert(true);
}

static void test_repo_dict_probability_one() {
	RepoDict rep{ 1 };
	const Carte c{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };

	try { rep.repoSize(); assert(false); }
	catch (const RepoError& e) { assert(e.getMessage().find("random") != string::npos); }

	try { rep.addCarte(c); assert(false); }
	catch (const RepoError& e) { assert(e.getMessage().find("random") != string::npos); }

	try { rep.deleteCarte(1); assert(false); }
	catch (const RepoError& e) { assert(e.getMessage().find("random") != string::npos); }

	try { rep.updateCarte(c); assert(false); }
	catch (const RepoError& e) { assert(e.getMessage().find("random") != string::npos); }

	try { rep.getById(1); assert(false); }
	catch (const RepoError& e) { assert(e.getMessage().find("random") != string::npos); }

	try { rep.getAll(); assert(false); }
	catch (const RepoError& e) { assert(e.getMessage().find("random") != string::npos); }
}

static void test_repo_dict_invalid_probability() {
	try {
		RepoDict rep{ -0.1 };
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Probabilitatea") != string::npos);
	}

	try {
		RepoDict rep{ 1.1 };
		assert(false);
	}
	catch (const RepoError& e) {
		assert(e.getMessage().find("Probabilitatea") != string::npos);
	}
}

void test_all_repo() {
	test_add_repo();
	test_delete_repo();
	test_update_repo();
	test_get_by_id_repo();
	test_get_all_repo();
	test_file_repo_load_missing_file();
	test_file_repo_load_valid_file_and_skip_empty_lines();
	test_file_repo_persists_add_update_delete();
	test_file_repo_invalid_missing_fields();
	test_file_repo_invalid_id();
	test_file_repo_invalid_year();
	test_file_repo_write_error();
	test_repo_dict_probability_zero();
	test_repo_dict_add_duplicate();
	test_repo_dict_delete();
	test_repo_dict_update();
	test_repo_dict_get_all_ordered_by_id();
	test_repo_dict_accepts_decimal_probabilities();
	test_repo_dict_probability_one();
	test_repo_dict_invalid_probability();
}
