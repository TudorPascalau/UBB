#include "IteratorLI.h"
#include "LI.h"
#include <exception>

// Theta(1)
IteratorLI::IteratorLI(const LI& li): lista(li) {
	this->curent = lista.prim;
}

// Theta(1)
void IteratorLI::prim(){
	this->curent = lista.prim;
}

// Theta(1)
void IteratorLI::urmator(){
	if(!valid())
		throw std::exception();

	this->curent = this->curent->urmator();
}

// Theta(1)
bool IteratorLI::valid() const{
	return this->curent != nullptr;
}

// Theta(1)
TElem IteratorLI::element() const{
	if(!valid())
		throw std::exception();

	return this->curent->element();
}
