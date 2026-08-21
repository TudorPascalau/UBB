#include "Validator.h"

void Validator::validate(int id, const string& descriere, const vector<string>& programatori, const string& stare)
{
	bool ok = true;
	string message = "";
	if (descriere == "") {
		ok = false;
		message += "Descriere vida! ";
	}

	if (stare != "closed" && stare != "open" && stare != "inprogress") {
		ok = false;
		message += "Stare invalida! ";
	}

	if (programatori.size() < 1 || programatori.size() > 4) {
		ok = false;
		message += "Numar programatori invalid! ";
	}

	if (!ok) {
		throw(ValidatorException(message));
	}
}
