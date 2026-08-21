#include <cassert>
#include <string>
using std::string;

#include "TestDomain.h"


static void test_creeaza_carte() {
	Carte c{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	assert(c.getId() == 1);
	assert(c.getTitlu() == "Moara cu noroc");
	assert(c.getAutor() == "Ioan Slavici");
	assert(c.getGen() == "Nuvela psihologica");
	assert(c.getAn() == 1881);

}

static void test_seteaza_carte() {
	Carte c{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	
	c.setTitlu("Ion");
	assert(c.getTitlu() == "Ion");

	c.setAutor("Liviu Rebreanu");
	assert(c.getAutor() == "Liviu Rebreanu");

	c.setGen("Roman realist");
	assert(c.getGen() == "Roman realist");

	c.setAn(1920);
	assert(c.getAn() == 1920);
}

static void test_equal_carte() {
	Carte c1{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c2{ 1,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };
	Carte c3{ 2,"Moara cu noroc","Ioan Slavici", "Nuvela psihologica", 1881 };

	assert(c1 == c2);
	assert(c1 != c3);
}

void TestDomain::test_all_domain() const {
	test_creeaza_carte();
	test_seteaza_carte();
	test_equal_carte();
}