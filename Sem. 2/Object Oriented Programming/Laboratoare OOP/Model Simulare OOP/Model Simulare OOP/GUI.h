#pragma once

#include "Service.h"

#include <QWidget>
#include <QListWidget>
#include <QPushButton>

class GUI : public QWidget
{
private:

	Service& service;

    QListWidget* list;
	QPushButton* btnInchiriaza;
	QPushButton* btnSortMarime;
	QPushButton* btnSortPret;
	QPushButton* btnNesortat;

	void initGUI();
	void connectSignals();
	void loadData(const vector<Rochie>& rochii);

public:
    GUI(Service& srv);
    
};

