#include "TestDomain.h"
#include "Carte.h"

#include <cassert>

void testDomain() {
	Carte c = Carte(1, "Moara cu Noroc", "Ioan Slavici", 25);
	assert(c.getId() == 1);
	assert(c.getTitlu() == "Moara cu Noroc");
	assert(c.getAutor() == "Ioan Slavici");
	assert(c.getPret() == 25);
	c.setPret(30);
	assert(c.getPret() == 30);
}