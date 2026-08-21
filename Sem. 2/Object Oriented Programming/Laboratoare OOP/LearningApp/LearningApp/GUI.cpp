#include "GUI.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

GUI::GUI(Service& service) : service(service)
{
	initGUI();
	connectSignals();
	loadData(service.getAllCarti());
}

GUI::~GUI() {}

void GUI::initGUI() {
	listCarti = new QListWidget(this);
	auto layout = new QVBoxLayout(this);

	layout->addWidget(listCarti);

	txtId = new QLineEdit(this);
	txtTitlu = new QLineEdit(this);
	txtAutor = new QLineEdit(this);
	txtPret = new QLineEdit(this);

	auto* formLayout = new QFormLayout();
	formLayout->addRow("ID:", txtId);
	formLayout->addRow("Titlu:", txtTitlu);
	formLayout->addRow("Autor:", txtAutor);
	formLayout->addRow("Pret:", txtPret);

	layout->addLayout(formLayout);

	btnAdd = new QPushButton("Adauga", this);
	layout->addWidget(btnAdd);

	setLayout(layout);
	resize(700, 400);


}

void GUI::connectSignals() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, [&]() {
		int id, pret;
		string titlu, autor;

		bool ok = readForm(id, titlu, autor, pret);
		if (!ok) {
			QMessageBox::warning(this, "Eroare", "Datele introduse sunt invalide.");
			return;
		}

		try {
			service.adaugaCarte(id, titlu, autor, pret);
			loadData(service.getAllCarti());

		}
		catch (const exception& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}
	});
}

void GUI::loadData(vector<Carte> carti) {
	listCarti->clear();
	for (const auto& carte : carti) {
		listCarti->addItem(QString::fromStdString(carte.getTitlu() + " - " + carte.getAutor()));
	}
}

bool GUI::readForm(int& id, string& titlu, string& autor, int& pret) {
	
	bool ok = false;
	id = txtId->text().toInt(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Eroare", "ID-ul trebuie să fie un număr întreg.");
		return false;
	}

	titlu = txtTitlu->text().toStdString();
	autor = txtAutor->text().toStdString();
	pret = txtPret->text().toInt(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Eroare", "Prețul trebuie să fie un număr real.");
		return false;
	}
	return true;
}