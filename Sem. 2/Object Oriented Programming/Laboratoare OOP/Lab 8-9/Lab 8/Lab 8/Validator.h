#pragma once

#include "Carte.h"

class ValidationError {
	private:
		string message;

	public:

		/*
		* Constructor pentru clasa ValidationError
		* @param message: mesajul de eroare
		* pre: message este de tip string
		* post: este creat un obiect de tip ValidationError
		* 
		*/
		explicit ValidationError(const string& message) : message{ message } {
		}


		/*
		* Returneaza mesajul de eroare
		* pre: -
		* post: nu se modifica obiectul
		* @return: mesajul de eroare
		*/
		const string& getMessage() const noexcept{
			return message;
		}
};

class Validator
{
public:

	/*
	* Valideaza datele unei carti
	* @param c: cartea de validat
	* pre: c este de tip Carte
	* post: daca datele nu sunt valide, se arunca exceptie
	*/
	void validate(const Carte& c) const;
};

