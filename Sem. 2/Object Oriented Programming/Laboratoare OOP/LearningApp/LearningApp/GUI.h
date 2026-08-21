#pragma once

#include <QtWidgets/QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

#include "Service.h"

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Service& service);
    ~GUI();

private:
	Service& service;

    void initGUI();
    void connectSignals();
    void loadData(vector<Carte> carti);

    bool readForm(int& id, string& titlu, string& autor, int& pret);

	QListWidget* listCarti;

	QLineEdit* txtId;
	QLineEdit* txtTitlu;
	QLineEdit* txtAutor;
    QLineEdit* txtPret;

	QPushButton* btnAdd;
};

