#include "TestDomain.h"

#include "Rochie.h"
#include <cassert>

void testDomain() {
	Rochie rochie = Rochie(1, "GUCCI WOOL DRESS", "S", 9000, true);
	assert(rochie.getCod() == 1);
	assert(rochie.getDenumire() == "GUCCI WOOL DRESS");
	assert(rochie.getMarime() == "S");
	assert(rochie.getPret() == 9000);
	assert(rochie.getDisponibil() == true);

	rochie.setDisponibil(false);
	assert(rochie.getDisponibil() == false);
}