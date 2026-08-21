#include "GUI.h"

#include <QAbstractItemView>

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
	createMainLayout();

	setLayout(mainLy);
	resize(1300, 800);

	openWindow = new StateWindow{ srv, taskModel, "open" };
	inprogressWindow = new StateWindow{ srv, taskModel, "inprogress" };
	closedWindow = new StateWindow{ srv, taskModel, "closed" };

	openWindow->show();
	inprogressWindow->show();
	closedWindow->show();
}

void GUI::connectSignals()
{
	connectAdd();
	connectFilter();
}

void GUI::reloadData()
{
	auto sortate = srv.getSortatStare();
	if(nameFilter->text() == "") {
		taskModel->setTasks(sortate);
	}

	else {
		string nume = nameFilter->text().toStdString();
		taskModel->setTasks(srv.filterNume(nume));
	}
}

void GUI::createTable()
{
	taskView = new QTableView{ this };
	taskModel = new TaskTableModel{ this };

	taskView->setModel(taskModel);
	taskView->setSelectionBehavior(QAbstractItemView::SelectRows);
	taskView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void GUI::createSideLayout()
{
	sideLy = new QVBoxLayout;

	idLbl = new QLabel{"Id", this};
	descLbl = new QLabel{"Descriere", this};
	progLbl = new QLabel{"Programatori (separati dupa ,)", this};
	stareLbl = new QLabel{"Stare", this};

	idTxt = new QLineEdit{this};
	descTxt = new QLineEdit{ this };
	progTxt = new QLineEdit{ this };
	stareTxt = new QLineEdit{ this };

	btnAdd = new QPushButton{ "Adaugare", this };

	nameLbl = new QLabel{ "Filtru nume (exact)", this };
	nameFilter = new QLineEdit{this };

	sideLy->addWidget(idLbl);
	sideLy->addWidget(idTxt);
	sideLy->addWidget(descLbl);
	sideLy->addWidget(descTxt);
	sideLy->addWidget(progLbl);
	sideLy->addWidget(progTxt);
	sideLy->addWidget(stareLbl);
	sideLy->addWidget(stareTxt);

	sideLy->addWidget(btnAdd);

	sideLy->addWidget(nameLbl);
	sideLy->addWidget(nameFilter);
	sideLy->addStretch();
}

void GUI::createMainLayout()
{
	mainLy = new QHBoxLayout;
	mainLy->addWidget(taskView);
	mainLy->addLayout(sideLy);
}

void GUI::connectAdd()
{
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {

		try {
			bool ok;
			int id = idTxt->text().toInt(&ok);
			if (!ok) {
				throw(ValidatorException("Id nu e intreg"));
			}

			string descriere = descTxt->text().toStdString();
			string prog = progTxt->text().toStdString();
			string stare = stareTxt->text().toStdString();

			vector<string> programatori;
			std::stringstream pstream(prog);
			string programator;
			while (getline(pstream, programator, ',')) {
				programatori.push_back(programator);
			}

			srv.adauga(id, descriere, programatori, stare);

		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Eroare repo", e.what());
		}
		catch (ValidatorException& e) {
			QMessageBox::warning(this, "Eroare validare", e.what());
		}

		reloadData();


		});
}

void GUI::connectFilter()
{
	QObject::connect(nameFilter, &QLineEdit::textChanged, [&]() {

		reloadData();

		});
}
