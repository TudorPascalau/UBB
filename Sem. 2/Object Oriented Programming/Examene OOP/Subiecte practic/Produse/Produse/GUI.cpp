#include "GUI.h"

#include <QAbstractItemView>
#include <QMessageBox>
#include <QHeaderView>

GUI::GUI(Service& srv, QWidget* parent) : QWidget(parent), srv{ srv }
{
	initGUI();
	connectSignals();
	reloadData();
}

GUI::~GUI()
{}

void GUI::initGUI()
{
	createTable();
	createSideLayout();
	createMainLayout();

	setLayout(mainLayout);
	resize(1300, 800);
}

void GUI::connectSignals()
{
	connectBtnAdd();
	connectSlidePret();
}

void GUI::reloadData()
{
	produsModel->setProduse(srv.getSortatPret());

	reloadWindows();
}

void GUI::reloadWindows()
{
	auto raport = srv.getRaportTip();
	for (const auto& [tip, count] : raport) {
		if (!windows.contains(tip)) {
			auto* w = new ProductWindow{ count, tip };
			windows[tip] = w;
			w->show();
		}
		else {
			windows[tip]->setCount(count);
		}
	}
}

void GUI::createTable()
{
	produsView = new QTableView{ this };
	produsModel = new ProdusTableModel{ this };

	produsView->setModel(produsModel);
	produsView->setSelectionBehavior(QAbstractItemView::SelectRows);
	produsView->setSelectionMode(QAbstractItemView::SingleSelection);
	produsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void GUI::createSideLayout()
{
	QLabel* idLabel = new QLabel{ "Id: ", this };
	QLabel* numeLabel = new QLabel{ "Nume: ", this };
	QLabel* tipLabel = new QLabel{"Tip: ", this};
	QLabel* pretLabel = new QLabel{ "Pret: ", this };

	idTxt = new QLineEdit{ this };
	numeTxt = new QLineEdit{ this };
	tipTxt = new QLineEdit{ this };
	pretTxt = new QLineEdit{ this };

	sideLayout = new QVBoxLayout;
	sideLayout->addWidget(idLabel);
	sideLayout->addWidget(idTxt);

	sideLayout->addWidget(numeLabel);
	sideLayout->addWidget(numeTxt);

	sideLayout->addWidget(tipLabel);
	sideLayout->addWidget(tipTxt);

	sideLayout->addWidget(pretLabel);
	sideLayout->addWidget(pretTxt);

	btnAdd = new QPushButton{ "Adauga", this };
	sideLayout->addWidget(btnAdd);

	slidePret = new QSlider{ Qt::Horizontal, this };
	slidePret->setMinimum(0);
	slidePret->setMaximum(100);
	sideLayout->addWidget(slidePret);

	sideLayout->addStretch();
}

void GUI::createMainLayout()
{
	mainLayout = new QHBoxLayout;
	mainLayout->addWidget(produsView);
	mainLayout->addLayout(sideLayout);
}

void GUI::readForms(int& id, string& nume, string& tip, double& pret)
{
	string message = "";

	bool ok;
	id = idTxt->text().toInt(&ok);
	if (!ok) {
		message += "Id invalid! ";
	}

	nume = numeTxt->text().toStdString();
	tip = tipTxt->text().toStdString();

	pret = pretTxt->text().toDouble(&ok);
	if (!ok) {
		message += "Pret invalid! ";
		throw(ValidatorException(message));
	}
}

void GUI::connectBtnAdd()
{
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {

		int id;
		string nume, tip;
		double pret;

		try {
			readForms(id, nume, tip, pret);
		}
		catch (ValidatorException& e) {
			QMessageBox::warning(this, "Eroare validare", e.what());
		}

		try {
			srv.adauga(id, nume, tip, pret);
		}
		catch (ValidatorException& e) {
			QMessageBox::warning(this, "Eroare validare", e.what());
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Eroare repo", e.what());
		}

		reloadData();

		});

	
}

void GUI::connectSlidePret()
{
	QObject::connect(slidePret, &QSlider::valueChanged, [&]() {

		double pret = slidePret->value();
		produsModel->setPret(pret);

		});
}

