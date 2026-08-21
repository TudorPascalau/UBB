#include "Test.h"
#include "Service.h"


#include <cassert>

void Test::testDomain() {
	Articol a(1, "Brand", "Categorie", "Marime");
	assert(a.getCod() == 1);
	assert(a.getCategorie() == "Categorie");
	assert(a.getBrand() == "Brand");
	assert(a.getMarime() == "Marime");
}

void Test::testRepository() {
	Repo repo("test.txt");
	assert(repo.getAll().size() == 12);
}

void Test::testService() {
	Repo repo("test.txt");
	Service service(repo);

	assert(service.getAllArticole().size() == 12);
	auto filtered = service.filterByBrand("Nike");
	assert(filtered.size() == 3);
	assert(filtered[0].getBrand() == "Nike");
	assert(filtered[1].getBrand() == "Nike");
	assert(filtered[2].getBrand() == "Nike");

	auto sorted = service.sortByMarime();
	assert(sorted.size() == 12);
	assert(sorted[0].getMarime() == "L");
	assert(sorted[4].getMarime() == "M");
}
