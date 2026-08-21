#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

class Meniu {
	int pret;
public:
	Meniu(int pret) : pret(pret) {}
	virtual string descriere() = 0;
	virtual int getPret() {
		return pret;
	}
	virtual ~Meniu() = default;
};

class CuCafea : public Meniu {
	Meniu* meniu;
public:
	CuCafea(Meniu* meniu) : Meniu(meniu->getPret()), meniu{ meniu } {}
	string descriere() override {
		return meniu->descriere() + " cu cafea";
	}

	int getPret() override {
		return Meniu::getPret() + 5;
	}

	~CuCafea() override {
		delete meniu;
	}
};

class CuRacoritoare : public Meniu {
	Meniu* meniu;
public:
	CuRacoritoare(Meniu* meniu) : Meniu(meniu->getPret()), meniu{ meniu } {}
	string descriere() override {
		return meniu->descriere() + " cu racoritoare";
	}

	int getPret() override {
		return Meniu::getPret() + 4;
	}

	~CuRacoritoare() override {
		delete meniu;
	}
};

class MicDejun : public Meniu {
	string denumire;
public:
	MicDejun(string denumire) : Meniu(denumire == "Ochiuri" ? 10 : 15), denumire(denumire) {}
	string descriere() override {
		return denumire;
	}
};

vector<Meniu*> menus() {
	vector<Meniu*> v;
	v.push_back(new CuCafea{ new CuRacoritoare{new MicDejun{"Omleta"} } });
	v.push_back(new CuCafea(new MicDejun("Ochiuri")));
	v.push_back(new MicDejun("Omleta"));
	return v;
}