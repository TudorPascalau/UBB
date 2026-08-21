#include "Validator.h"

void Validator::validate(string nume, double pret) const
{
	bool ok = true;
	string message = "";
	if (nume == "") {
		message += "Nume invalid! ";
		ok = false;
	}

	if (pret < 1.0 || pret > 100.0) {
		message += "Pret invalid! ";
		ok = false;
	}

	if (!ok) {
		throw(ValidatorException(message));
	}
	
}
