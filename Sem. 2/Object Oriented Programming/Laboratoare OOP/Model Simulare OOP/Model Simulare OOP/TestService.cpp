#include "TestService.h"

#include "Service.h"
#include <cassert>

void testService() {
	Repo repo("test.txt");
	Service srv(repo);

	auto& rochii = srv.getAllNesortat();
	assert(rochii.size() == 3);

	srv.inchireaza(1);
	try {
		srv.inchireaza(1);
		assert(false);
	}
	catch (RepoError& re) {
		assert(re.getMessage() == "Rochie indisponibila!");
	}

	auto rez = srv.sortPret();
	assert(rez[0].getCod() == 2);

	rez = srv.sortMarime();
	assert(rez[0].getCod() == 3);
}