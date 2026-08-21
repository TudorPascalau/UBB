#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

class Smoothy
{
	int pret;
public:
	Smoothy(int pret) : pret(pret) {}
	virtual int getPret() const { 
		return pret; 
	}

	virtual string descriere() = 0;

	virtual ~Smoothy() = default;
};

class BasicSmoothy : public Smoothy 
{
	string nume;
public:
	BasicSmoothy(int pret, string nume) : Smoothy(pret), nume(nume) {}
	string descriere() override {
		return nume;
	}
};

class DecoratorSmoothy : public Smoothy
{
	Smoothy* smooty;
public:
	DecoratorSmoothy(Smoothy* s) : Smoothy(s->getPret()), smooty(s) {}
	int getPret() const override {
		return smooty->getPret();
	}
	string descriere() override {
		return smooty->descriere();
	}

	virtual ~DecoratorSmoothy() {
		delete smooty;
	}
};

class SmoothyCuFrisca : public DecoratorSmoothy
{
public:

	SmoothyCuFrisca(Smoothy* s) : DecoratorSmoothy(s) {}

	int getPret() const override {
		return DecoratorSmoothy::getPret() + 2;
	}

	string descriere() override {
		return DecoratorSmoothy::descriere() + " cu frisca";
	}
};

class SmoothyCuUmbreluta : public DecoratorSmoothy
{
public:

	SmoothyCuUmbreluta(Smoothy* s) : DecoratorSmoothy(s) {}

	int getPret() const override {
		return DecoratorSmoothy::getPret() + 3;
	}
	string descriere() override {
		return DecoratorSmoothy::descriere() + " cu umbreluta";
	}
};

vector<Smoothy*> smoothies() {
	vector<Smoothy*> v;
	v.push_back(new SmoothyCuFrisca(new SmoothyCuUmbreluta(new BasicSmoothy{ 10, "kiwi" })));
	v.push_back(new SmoothyCuFrisca(new BasicSmoothy(10, "capsuni")));
	v.push_back(new BasicSmoothy(10, "kiwi"));
	return v;
}
