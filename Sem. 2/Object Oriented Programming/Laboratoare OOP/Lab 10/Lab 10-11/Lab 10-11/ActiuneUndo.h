#pragma once

#include "AbstractRepo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	RepoAbstract& rep;
	int idCarteAdaugata;

public:
	UndoAdauga(RepoAbstract& rep, int idCarteAdaugata) : rep{ rep }, idCarteAdaugata{ idCarteAdaugata } {
	}

	void doUndo() override {
		rep.deleteCarte(idCarteAdaugata);
	}
};

class UndoSterge : public ActiuneUndo {
private:
	RepoAbstract& rep;
	Carte carteStearsa;

public:
	UndoSterge(RepoAbstract& rep, const Carte& carteStearsa) : rep{ rep }, carteStearsa{ carteStearsa } {
	}

	void doUndo() override {
		rep.addCarte(carteStearsa);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	RepoAbstract& rep;
	Carte carteVeche;

public:
	UndoModifica(RepoAbstract& rep, const Carte& carteVeche) : rep{ rep }, carteVeche{ carteVeche } {
	}

	void doUndo() override {
		rep.updateCarte(carteVeche);
	}
};
