#pragma once

#include "Service.h"

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class GUI : public QWidget
{
    Q_OBJECT

public:
	/*
	* Constructor pentru GUI
	* @param service: service-ul asociat interfetei grafice
	*/
	GUI(Service& service);
    ~GUI();

private:
	Service& service;

	QListWidget* lstArticole;
	QPushButton* btnReset;
	QPushButton* btnFilterBrand;
	QPushButton* btnSortMarime;

	QLineEdit* lineBrand;
	QLabel* listSelection;

	/*
	* Metoda ce initializeaza componentele GUI si formeaza layout-ul
	*/
	void initGUI();

	/*
	* Metoda ce face legatura intre semnale si sloturi pentru butoane si selectii
	*/
	void connectSignals();

	/*
	* Metoda ce incarca in lista din GUI articolele
	* @param articole: vector<Articol> ce contine articolele pe care dorim sa le afisam
	*/
	void reloadList(const vector<Articol>& articole);
};

