#include "GUI.h"

#include <QAbstractItemView>
#include <QMessageBox>

GUI::GUI(Service& srv, QWidget* parent) : QWidget(parent), srv{srv}
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
	createTopLayout();
	createGameLayout();
	createMainLayout();

	setLayout(mainLayout);
	resize(1300, 800);
}

void GUI::connectSignals()
{
	connectAddButton();
	connectTableSelect();
	connectBtnModifica();
}

void GUI::reloadData()
{
	clearBoard();
	xoModel->setJocuri(srv.getSortatStare());
	xoView->clearSelection();
}

void GUI::clearBoard()
{
	while (boardLayout->count()) {
		auto item = boardLayout->takeAt(0);
		delete item->widget();
		delete item;
	}

	boardButtons.clear();
}

void GUI::reloadBoard(const XO& j)
{
	clearBoard();

	int id = j.getId();
	int dim = j.getDim();
	string tabla = j.getTabla();
	string player = j.getPlayer();
	string stare = j.getStare();

	for(int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			auto* btn = new QPushButton;
			boardLayout->addWidget(btn, i, j);
			boardButtons.push_back(btn);

			int poz = i * dim + j;

			char c = tabla[poz];
			btn->setText(QString(c));

			QObject::connect(btn, &QPushButton::clicked, [=]() {


				try {

					if (tabla[poz] != '-') {
						throw(RepoException("Loc ocupat! "));
					}

					string newTable = tabla;
					newTable[poz] = player[0];

					string newPlayer = "";
					if (player == "X") {
						newPlayer = "O";
					}
					else {
						newPlayer = "X";
					}

					srv.modifica(id, dim, newTable, newPlayer, stare);
					reloadData();
				}
				catch (ValidatorException& ex) {
					QMessageBox::warning(this, "Eroare validare", ex.what());
				}
				catch (RepoException& ex) {
					QMessageBox::warning(this, "Eroare repo", ex.what());
				}

			});
		}
}

void GUI::createTable()
{
	xoView = new QTableView{ this };
	xoModel = new XOTableModel{ this };

	xoView->setModel(xoModel);
	xoView->setSelectionBehavior(QAbstractItemView::SelectRows);
	xoView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void GUI::createSideLayout()
{
	sideLayout = new QVBoxLayout;

	auto* dimLbl = new QLabel{ "Dimensiune", this };
	dimTxt = new QLineEdit{ this };
	sideLayout->addWidget(dimLbl);
	sideLayout->addWidget(dimTxt);

	auto* tableLbl = new QLabel{ "Tabla", this };
	tableTxt = new QLineEdit{ this };
	sideLayout->addWidget(tableLbl);
	sideLayout->addWidget(tableTxt);

	auto* playerLbl = new QLabel{ "Jucator", this };
	playerTxt = new QLineEdit{ this };
	sideLayout->addWidget(playerLbl);
	sideLayout->addWidget(playerTxt);

	auto* stareLbl = new QLabel{ "Stare", this };
	stareTxt = new QLineEdit{ this };
	sideLayout->addWidget(stareLbl);
	sideLayout->addWidget(stareTxt);

	btnAdd = new QPushButton{ "Adauga", this };
	sideLayout->addWidget(btnAdd);

	btnModifica = new QPushButton{ "Modifica", this };
	sideLayout->addWidget(btnModifica);

	sideLayout->addStretch();

}

void GUI::createTopLayout()
{
	topLayout = new QHBoxLayout;
	topLayout->addWidget(xoView);
	topLayout->addLayout(sideLayout);
}

void GUI::createGameLayout()
{
	boardWidget = new QWidget;
	boardLayout = new QGridLayout;
	boardWidget->setLayout(boardLayout);
}

void GUI::createMainLayout()
{
	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(boardWidget);
}

void GUI::connectAddButton()
{
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {

		try {
			bool ok;
			int dim = dimTxt->text().toInt(&ok);
			if (!ok) {
				throw(ValidatorException("Dimensiunea nu este un intreg! "));
			}

			string table = tableTxt->text().toStdString();
			string player = playerTxt->text().toStdString();

			srv.adauga(dim, table, player);

		}
		catch (ValidatorException& ex) {
			QMessageBox::warning(this, "Eroare validare", ex.what());
		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Eroare repo", ex.what());
		}

		reloadData();

	});
}

void GUI::connectTableSelect()
{
	QObject::connect(xoView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {

		auto indexes = xoView->selectionModel()->selectedIndexes();
		if (indexes.isEmpty()) {
			idSelect = -1;
			return;
		}

		int row = indexes.at(0).row();
		auto cel0Index = xoModel->index(row, 0);

		int id = xoModel->data(cel0Index).toInt();
		idSelect = id;

		auto joc = srv.getJocById(idSelect);
		reloadBoard(joc);

	});
}

void GUI::connectBtnModifica()
{
	QObject::connect(btnModifica, &QPushButton::clicked, [&]() {

		try {

			if (idSelect == -1) {
				throw(ValidatorException("Niciun joc selectat! "));
			}

			int id = idSelect;
			bool ok;
			int dim = dimTxt->text().toInt(&ok);
			if (!ok) {
				throw(ValidatorException("Dimensiunea nu este un intreg! "));
			}

			string table = tableTxt->text().toStdString();
			string player = playerTxt->text().toStdString();
			string stare = stareTxt->text().toStdString();

			srv.modifica(id, dim, table, player, stare);
			
		}
		catch (ValidatorException& ex) {
			QMessageBox::warning(this, "Eroare validare", ex.what());
		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Eroare repo", ex.what());
		}

		reloadData();

	});
}
