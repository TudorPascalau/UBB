#include "Validator.h"

void Validator::validate(int id, const string& denumire, const string& tip, int nrRoti) const
{
	string errors;
	if (id <= 0)
		errors += "ID invalid! ";
	if (denumire.empty())
		errors += "Denumire invalida! ";
	if (tip.empty())
		errors += "Tip invalid! ";
	if (nrRoti % 2 != 0 || nrRoti < 2 || nrRoti > 16)
		errors += "Numar de roti invalid! ";
	if (!errors.empty())
		throw ValidatorException(errors);
}