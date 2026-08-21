#include <iostream>
using std::cout;

#include "Carte.h"

int Carte::getId() const noexcept{
	return this->id;
}

const string& Carte::getTitlu() const noexcept{
	return this->titlu;
}

const string& Carte::getAutor() const noexcept{
	return this->autor;
}

const string& Carte::getGen() const noexcept{
	return this->gen;
}

int Carte::getAn() const noexcept{
	return this->an;
}

void Carte::setTitlu(const string& newTitlu) noexcept{
	this->titlu = newTitlu;
}

void Carte::setAutor(const string& newAutor) noexcept{
	this->autor = newAutor;
}

void Carte::setGen(const string& newGen) noexcept{
	this->gen = newGen;
}

void Carte::setAn(int newAn) noexcept{
	this->an = newAn;
}

bool Carte::operator==(const Carte& ot) const {
	return (this->id == ot.id && this->titlu == ot.titlu && this->autor == ot.autor && this->gen == ot.gen && this->an == ot.an);
}