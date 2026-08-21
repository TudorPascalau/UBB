#include "TestRepo.h"
#include "Repo.h"

#include <cassert>
#include <fstream>

void testRepo() {
	
	std::ofstream out("test.txt");

	out << "1,Small Red Dress,S,4000,true\n";

	out.close();

	Repo repo("test.txt");
	repo.addRochie(Rochie(2, "Small Blue Dress", "S", 3000, false));
	try {
		repo.addRochie(Rochie(1, "GUCCI WOOL DRESS", "S", 9000, true));
		assert(false);
	}
	catch (RepoError& re) {
		assert(re.getMessage() == "Cod deja existent!");
	}

	repo.addRochie(Rochie(3, "Medium Red Dress", "M", 4000, true));

	auto all = repo.getAll();
	assert(all.size() == 3);
}