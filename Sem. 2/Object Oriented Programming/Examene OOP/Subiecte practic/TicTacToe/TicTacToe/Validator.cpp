#include "Validator.h"

void Validator::validate(int dim, string table, string player, string stare)
{
	bool ok = true;
	string message = "";

	if (dim != 3 && dim != 4 && dim != 5) {
		ok = false;
		message += "Dimensiune invalida! ";
	}

	if(table.size() != dim*dim) {
		ok = false;
		message += "Dimensiune tabela invalida! ";
	}
	else {
		for (const auto& c : table) {
			if(c != 'X' && c != 'O' && c != '-') {
				ok = false;
				message += "Tabela invalida! ";
				break;
			}
		}
	}

	if (player != "X" && player != "O") {
		ok = false;
		message += "Jucator invalid! ";
	}

	if (stare != "Neinceput" && stare != "In derulare" && stare != "Terminat") {
		ok = false;
		message += "Stare invalida! ";
	}

	if (!ok) {
		throw(ValidatorException(message));
	}
}
