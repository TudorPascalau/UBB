#include "Iterator.h"
#include "DO.h"

using namespace std;

//returneaza pozitia primului element din container sau -1 daca containerul e vid
//Theta(m)
int Iterator::CautaPrim() const {
	int pozPrim = -1;

	for (int i = 0; i < dict.m; i++) {
		if (dict.ocupat[i]) {
			if (pozPrim == -1 || dict.rel(dict.e[i].first, dict.e[pozPrim].first)) {
				pozPrim = i;
			}
		}
	}

	return pozPrim;
}

//returneaza pozitia urmatorului element din container dupa pozitia poz sau -1 daca poz e ultima pozitie sau containerul e vid
//Theta(m)
int Iterator::CautaUrmator(int poz) const {
	int pozUrm = -1;
	TCheie cheieCurenta = dict.e[poz].first;

	for (int i = 0; i < dict.m; i++) {
		if (dict.ocupat[i]) {
			TCheie cheie = dict.e[i].first;

			if (cheie != cheieCurenta && dict.rel(cheieCurenta, cheie)) {
				if (pozUrm == -1 || dict.rel(cheie, dict.e[pozUrm].first)) {
					pozUrm = i;
				}
			}
		}
	}

	return pozUrm;
}

//Theta(m)
Iterator::Iterator(const DO& d) : dict(d){
	curent = CautaPrim();
}

//Theta(m)
void Iterator::prim(){
	curent = CautaPrim();
}

//Theta(m)
void Iterator::urmator(){
	if (!valid()) {
		throw exception();
	}
	curent = CautaUrmator(curent);
}

//Theta(1)
bool Iterator::valid() const{
	return curent != -1;
}

//Theta(1)
TElem Iterator::element() const{
	if (!valid()) {
		throw exception();
	}

	return dict.e[curent];

}



