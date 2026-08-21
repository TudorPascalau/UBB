#include <cassert>

#include "TestList.h"
#include "Carte.h"

static void test_add_list() {
	Lista<Carte> l;
	Carte c{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };

	l.add(c);
	assert(l.size() == 1);
	assert(l.getElem(0) == c);
}

static void test_remove_list() {
	Lista<Carte> l;
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 2,"Ion","Liviu Rebreanu", "roman", 1920 };
	Carte c3{ 3,"Baltagul","Mihail Sadoveanu", "roman", 1930 };

	assert(l.size() == 0);

	l.add(c1);
	assert(l.size() == 1);
	l.remove(0);
	assert(l.size() == 0);

	l.add(c1);
	l.add(c2);
	l.add(c3);

	l.remove(0);
	assert(l.size() == 2);
	assert(l.getElem(0) == c2);
	assert(l.getElem(1) == c3);
}

static void test_equal_list() {
	Lista<Carte> l1, l2;
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 2,"Ion","Liviu Rebreanu", "roman", 1920 };
	Carte c3{ 3,"Baltagul","Mihail Sadoveanu", "roman", 1930 };

	l1.add(c1);
	l2.add(c1);
	assert(l1 == l2);

	l1.remove(0);
	assert(l1 != l2);

	l1.add(c2);
	l2.remove(0);
	l2.add(c3);
	assert(l1 != l2);
}

static void test_iterator_empty_list() {
	Lista<Carte> l;

	auto itBegin = l.begin();
	auto itEnd = l.end();

	assert(l.size() == 0);
	assert(!itBegin.valid());
	assert(itBegin == itEnd);
	assert(!(itBegin != itEnd));
}

static void test_iterator_begin_end_valid() {
	Lista<Carte> l;
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 2,"Ion","Liviu Rebreanu", "roman", 1920 };

	l.add(c1);
	l.add(c2);

	auto it = l.begin();
	auto itEnd = l.end();

	assert(it.valid());
	assert(it != itEnd);
	assert(*it == c1);

	++it;
	assert(it.valid());
	assert(*it == c2);

	++it;
	assert(!it.valid());
	assert(it == itEnd);
}

static void test_iterator_element_and_next() {
	Lista<Carte> l;
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 2,"Ion","Liviu Rebreanu", "roman", 1920 };

	l.add(c1);
	l.add(c2);

	auto it = l.begin();

	assert(it.element() == c1);
	it.next();
	assert(it.element() == c2);
	it.next();
	assert(!it.valid());
}

static void test_iterator_operator_dereference_modify() {
	Lista<Carte> l;
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };

	l.add(c1);

	auto it = l.begin();
	(*it).setTitlu("Ion");

	assert(l.getElem(0).getTitlu() == "Ion");
}

static void test_iterator_comparison() {
	Lista<Carte> l;
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 2,"Ion","Liviu Rebreanu", "roman", 1920 };

	l.add(c1);
	l.add(c2);

	auto it1 = l.begin();
	auto it2 = l.begin();
	auto itEnd = l.end();

	assert(it1 == it2);
	assert(!(it1 != it2));

	++it2;
	assert(it1 != it2);
	assert(!(it1 == it2));

	++it1;
	assert(it1 == it2);

	++it1;
	assert(it1 == itEnd);
	assert(it1 != it2);
}

static void test_iterator_full_traversal() {
	Lista<Carte> l;
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 2,"Ion","Liviu Rebreanu", "roman", 1920 };
	Carte c3{ 3,"Baltagul","Mihail Sadoveanu", "roman", 1930 };

	l.add(c1);
	l.add(c2);
	l.add(c3);

	int count = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		const Carte& c = *it;
		assert(c.getId() >= 1);
		count++;
	}

	assert(count == 3);
}

static void test_iterator_foreach() {
	Lista<Carte> l;
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 2,"Ion","Liviu Rebreanu", "roman", 1920 };
	Carte c3{ 3,"Baltagul","Mihail Sadoveanu", "roman", 1930 };

	l.add(c1);
	l.add(c2);
	l.add(c3);

	int sumaId = 0;
	int count = 0;

	for (const auto& c : l) {
		sumaId += c.getId();
		count++;
	}

	assert(count == 3);
	assert(sumaId == 6);
}

void TestList::test_all_list() const {
	test_add_list();
	test_remove_list();
	test_equal_list();

	test_iterator_empty_list();
	test_iterator_begin_end_valid();
	test_iterator_element_and_next();
	test_iterator_operator_dereference_modify();
	test_iterator_comparison();
	test_iterator_full_traversal();
	test_iterator_foreach();
}