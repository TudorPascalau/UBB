#include "GUI.h"

#include <QListWidgetItem>

#include <sstream>
using std::stringstream;
using std::getline;

GUI::GUI(Service& service) : service(service)
{
	initGUI();
	connectSignals();
	reloadList(service.getAllArticole());
}

GUI::~GUI()
{}

void GUI::initGUI()
{
	lstArticole = new QListWidget;

	btnReset = new QPushButton("Reset");
	btnFilterBrand = new QPushButton("Filtrare dupa brand");
	btnSortMarime = new QPushButton("Sortare dupa marime");
	lineBrand = new QLineEdit;
	listSelection = new QLabel;
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(lstArticole);
	mainLayout->addWidget(btnReset);
	mainLayout->addWidget(btnFilterBrand);
	mainLayout->addWidget(lineBrand);
	mainLayout->addWidget(btnSortMarime);
	mainLayout->addWidget(listSelection);

	setLayout(mainLayout);
	resize(700, 400);
}

void GUI::connectSignals()
{
	QObject::connect(btnReset, &QPushButton::clicked, [&]() {
		lstArticole->clearSelection();
		reloadList(service.getAllArticole());
	});

	QObject::connect(btnSortMarime, &QPushButton::clicked, [&]() {
		lstArticole->clearSelection();
		reloadList(service.sortByMarime());
	});

	QObject::connect(btnFilterBrand, &QPushButton::clicked, [&]() {
		lstArticole->clearSelection();
		QString brand = lineBrand->text();
		reloadList(service.filterByBrand(brand.toStdString()));
	});

	QObject::connect(lstArticole, &QListWidget::itemSelectionChanged, [this]() {
		auto items = lstArticole->selectedItems();

		if (items.isEmpty()) {
			return;
		}

		auto item = items.at(0);

		string text = (item->text()).toStdString();
		string categorie, brand, marime;
		stringstream ss(text);

		getline(ss, brand, ',');
		getline(ss, categorie, ',');
		getline(ss, marime, ',');

		QString labelText = QString::fromStdString("Articoul " + categorie + " de la " + brand + " este disponibil in marimea " + marime);
		listSelection->setText(labelText);
	});

}

void GUI::reloadList(const vector<Articol>& articole)
{
	listSelection->clear();
	lstArticole->clear();
	for (const auto& a : articole) {
		QString itemText = QString::fromStdString(a.getBrand() + "," + a.getCategorie() + "," + a.getMarime());
		QListWidgetItem* item = new QListWidgetItem(itemText);
		item->setData(Qt::UserRole, a.getCod());
		if(a.getCategorie() == "minge") item->setBackground(QBrush(Qt::yellow));
		else if (a.getCategorie() == "racheta") item->setBackground(QBrush(Qt::green));
		else if (a.getCategorie() == "bicicleta") item->setBackground(QBrush(Qt::blue));
		else if (a.getCategorie() == "coarda") item->setBackground(QBrush(Qt::gray));
		else item->setBackground(QBrush(Qt::white));

		item->setForeground(QBrush(Qt::black));

		lstArticole->addItem(item);
	}
}
