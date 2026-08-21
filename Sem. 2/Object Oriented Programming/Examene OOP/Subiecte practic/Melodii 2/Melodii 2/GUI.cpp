#include "GUI.h"

#include <QMessageBox>
#include <QLabel>
#include <QAbstractItemView>

GUI::GUI(Service& srv, QWidget *parent) : QWidget(parent), srv(srv)
{
	initGUI();
	connectSignals();
	reloadData();
}

GUI::~GUI() {}

void GUI::initGUI()
{
	createTable();
	createLeftLayout();
	createTopLayout();
	createMainLayout();

	setLayout(mainLayout);
	resize(1300, 800);
}

void GUI::connectSignals()
{
	connectBtnAdauga();
	connectTableSelection();
	connectBtnSterge();
}

void GUI::reloadData()
{
	melodiiView->clearSelection();

	auto sortat = srv.getSortateArtist();
	melodiiModel->setMelodii(sortat);

	reloadCircles();
}

void GUI::reloadCircles()
{
	auto melodii = srv.getSortateArtist();

	int pop = 0, rock = 0, folk = 0, disco = 0;

	for (const auto& m : melodii) {
		if (m.getGen() == "pop") pop++;
		else if (m.getGen() == "rock") rock++;
		else if (m.getGen() == "folk") folk++;
		else if (m.getGen() == "disco") disco++;
	}

	popWidget->setNrMelodii(pop);
	rockWidget->setNrMelodii(rock);
	folkWidget->setNrMelodii(folk);
	discoWidget->setNrMelodii(disco);
}

void GUI::createTable()
{
	melodiiView = new QTableView{ this };
	melodiiModel = new MelodieTableModel{ this };
	melodiiView->setModel(melodiiModel);

	melodiiView->setSelectionBehavior(QAbstractItemView::SelectRows);
	melodiiView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void GUI::createLeftLayout()
{
	auto titluLbl = new QLabel{ "Titlu: " };
	auto artistLbl = new QLabel{ "Artist: " };
	auto genLbl = new QLabel{ "Gen: " };

	titluTxt = new QLineEdit{ this };
	artistTxt = new QLineEdit{ this };
	genTxt = new QLineEdit{ this };

	btnAdauga = new QPushButton{ "Adauga", this };
	btnSterge = new QPushButton{ "Sterge", this };

	leftLayout = new QVBoxLayout;
	leftLayout->addWidget(titluLbl);
	leftLayout->addWidget(titluTxt);

	leftLayout->addWidget(artistLbl);
	leftLayout->addWidget(artistTxt);

	leftLayout->addWidget(genLbl);
	leftLayout->addWidget(genTxt);
	leftLayout->addWidget(btnAdauga);
	leftLayout->addWidget(btnSterge);

	leftLayout->addStretch();

}

void GUI::createTopLayout()
{
	topLayout = new QHBoxLayout;
	topLayout->addWidget(melodiiView);
	topLayout->addLayout(leftLayout);
}

void GUI::createMainLayout()
{
	mainLayout = new QGridLayout;

	popWidget = new CircleWidget{ this };
	rockWidget = new CircleWidget{ this };
	folkWidget = new CircleWidget{ this };
	discoWidget = new CircleWidget{ this };

	mainLayout->addWidget(popWidget, 0, 0);
	mainLayout->addWidget(rockWidget, 0, 2);
	mainLayout->addWidget(folkWidget, 2, 0);
	mainLayout->addWidget(discoWidget, 2, 2);

	mainLayout->addLayout(topLayout, 1, 1);

}

void GUI::connectBtnAdauga()
{
	QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {

		string titlu = titluTxt->text().toStdString();
		string artist = artistTxt->text().toStdString();
		string gen = genTxt->text().toStdString();

		try {
			srv.adauga(titlu, artist, gen);
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Eroare", e.what());
		}

		reloadData();

	});

}

void GUI::connectTableSelection()
{
	QObject::connect(melodiiView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {

		auto indexes = melodiiView->selectionModel()->selectedIndexes();
		if (indexes.isEmpty()) {
			idSelected = -1;
			return;
		}

		int selRow = indexes.at(0).row();
		auto cel0Index = melodiiModel->index(selRow, 0);
		int id = melodiiModel->data(cel0Index).toInt();

		idSelected = id;

		});
}

void GUI::connectBtnSterge()
{
	QObject::connect(btnSterge, &QPushButton::clicked, [&]() {

		if (idSelected == -1) {
			QMessageBox::warning(this, "Eroare", "Nicio melodie selectata");
			return;
		}

		try {
			srv.sterge(idSelected);
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Eroare", e.what());
		}

		reloadData();

		});
}
