#include "Validator.h"

void Validator::validate(const Carte& c) const {
	string errors;

	if (c.getId() < 1)
		errors += "Id invalid.\n";

	if (c.getTitlu().empty())
		errors += "Titlu invalid.\n";

	if (c.getAutor().empty())
		errors += "Autor invalid.\n";

	if (c.getGen().empty())
		errors += "Gen invalid.\n";

	if (c.getAn() < 1)
		errors += "An invalid.\n";

	if (!errors.empty())
		throw ValidationError(errors);
}