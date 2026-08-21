#include "IteratorMD.h"
#include "MD.h"
#include <exception>

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	prim();
}

// Theta(1)
TElem IteratorMD::element() const{
	if(!valid())
		throw exception();

	return pair<TCheie, TValoare>(md.chei[curentCheie], md.valori[curentValoare]);
}

// Theta(1)
bool IteratorMD::valid() const {
	return curentCheie != -1 && curentValoare != -1;
}

// Theta(1)
void IteratorMD::urmator() {
	if(!valid())
		throw exception();

	if(md.urmValori[curentValoare] != -1)
		curentValoare = md.urmValori[curentValoare];
	else {
		curentCheie = md.urmChei[curentCheie];
		if(curentCheie != -1)
			curentValoare = md.primVal[curentCheie];
		else
			curentValoare = -1;
	}
}

// Theta(1)
void IteratorMD::prim() {
	curentCheie = md.primChei;

	if(curentCheie != -1)
		curentValoare = md.primVal[curentCheie];
	else
		curentValoare = -1;
}

