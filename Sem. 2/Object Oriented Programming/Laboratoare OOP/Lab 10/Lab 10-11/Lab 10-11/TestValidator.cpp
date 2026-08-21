#pragma once

#include <cassert>

#include "Validator.h"

void test_all_validator() {
	Validator val;

	Carte c{ 1, "Moara cu noroc", "Ioan Slavici", "Nuvela psihologica", 1881 };
	val.validate(c);
	assert(true);


	Carte c2{ 0, "", "", "", 0 };
	try {
		val.validate(c2);
		assert(false);
	}
	catch (const ValidationError& e) {
		string msg = e.getMessage();
		assert(msg.find("Id invalid") != string::npos);
		assert(msg.find("Titlu invalid") != string::npos);
		assert(msg.find("Autor invalid") != string::npos);
		assert(msg.find("Gen invalid") != string::npos);
		assert(msg.find("An invalid") != string::npos);
	}

}