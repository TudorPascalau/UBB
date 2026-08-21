#pragma once

#include "Service.h"

#include <string>

class UI
{
private:
	Service& srv;

	/*
	* Meniul principal al aplicatiei
	*/
	void printMenu() const;

	/*
	* Adaugare de sample data
	*/
	void addSampleData();

	/*
	* Afiseaza campurile unei carti
	*/
	void printCarte(const Carte& c) const;

	/*
	* Afiseaza toate elementele unei liste de carti
	*/
	void printLista(const Lista<Carte>& l) const;

	/*
	* Afiseaza toate elementele unei liste de indici
	*/
	void printListaIndex(const Lista<int>& l) const;

	/*
	* Afiseaza continutul cosului
	*/
	void printCos() const;


	/*
	* Citeste un intreg de la tastatura
	* @param mesaj: mesajul afisat
	*        val: valoarea citita
	* @return: true daca s-a citit corect un intreg, false altfel
	*/
	bool readInt(const string& mesaj, int& val) const;

	/*
	* Adauga o carte
	*/
	void uiAddCarte();

	/*
	* Sterge o carte
	*/
	void uiDeleteCarte();

	/*
	* Modifica o carte
	*/
	void uiUpdateCarte();

	/*
	* Cauta o carte si o afiseaza
	*/
	void uiFindCarte() const;

	/*
	* Afiseaza toate cartile
	*/
	void uiShowAll() const;

	/*
	* Sorteaza dupa titlu
	*/
	void uiSortByTitlu() const;

	/*
	* Sorteaza dupa autor
	*/
	void uiSortByAutor() const;

	/*
	* Sorteaza dupa an + gen
	*/
	void uiSortByAnGen() const;

	/*
	* Filtreaza dupa titlu
	*/
	void uiFilterByTitlu() const;

	/*
	* Filtreaza dupa an
	*/
	void uiFilterByAn() const;

	/*
	* Adauga o carte in cos dupa titlu
	*/
	void uiAdaugaCos();

	/*
	* Goleste cosul
	*/
	void uiGolesteCos();

	/*
	* Genereaza cos aleator
	*/
	void uiGenereazaCos();

	/*
	* Afiseaza cosul
	*/
	void uiShowCos() const;

	/*
	* Export in fisier CSV
	*/
	void uiExportCosCSV() const;

	/*
	* Raport cate carti sunt pentru fiecare gen
	*/
	void uiRaportGenuri() const;

public:
	/*
	* Constructorul clasei UI
	*/
	UI(Service& srv) : srv{ srv } {
	}

	/*
	* Nucleul aplicatiei
	*/
	void run();
};