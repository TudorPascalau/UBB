#include "GUI.h"

#include <QHeaderView>
#include <QAbstractItemView>
#include <QMessageBox>

GUI::GUI(Service& srv, QWidget* parent) : QWidget(parent), srv(srv)
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
	createFullLayout();

	setLayout(fullLayout);
	resize(1300, 800);
}

void GUI::connectSignals()
{
	connectTableSelection();
	connectBtnUpdate();
	connectBtnSterge();
}

void GUI::reloadData()
{
	const auto melodii = srv.getSortRank();

	melodiiTableView->clearSelection();
	melodiiTableModel->setMelodii(melodii);
	barWidget->setMelodii(melodii);

	idSelectat = -1;
	titluTxt->setText("");
	rankSlider->setValue(0);
}

void GUI::createTable()
{
	melodiiTableView = new QTableView{ this };
	melodiiTableModel = new MelodieTableModel{ this };

	melodiiTableView->setModel(melodiiTableModel);
	melodiiTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	melodiiTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	melodiiTableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void GUI::createLeftLayout()
{
	titluTxt = new QLineEdit{ this };

	rankSlider = new QSlider{ Qt::Horizontal ,this };
	rankSlider->setMinimum(0);
	rankSlider->setMaximum(10);
	rankSlider->setTickPosition(QSlider::TicksAbove);

	btnUpdate = new QPushButton{ "Modifica", this };
	btnSterge = new QPushButton{ "Sterge", this };

	leftLayout = new QVBoxLayout;
	leftLayout->addWidget(titluTxt);
	leftLayout->addWidget(rankSlider);
	leftLayout->addWidget(btnUpdate);
	leftLayout->addWidget(btnSterge);

	leftLayout->addStretch();
}

void GUI::createTopLayout()
{
	topLayout = new QHBoxLayout;
	topLayout->addWidget(melodiiTableView);
	topLayout->addLayout(leftLayout);
}

void GUI::createFullLayout()
{
	fullLayout = new QVBoxLayout;
	fullLayout->addLayout(topLayout);

	barWidget = new BarWidget{this};
	barWidget->setMinimumHeight(500);
	fullLayout->addWidget(barWidget);
}

void GUI::connectTableSelection()
{
	QObject::connect(melodiiTableView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		
		if (melodiiTableView->selectionModel()->selectedIndexes().isEmpty()) {
			titluTxt->setText("");
			rankSlider->setValue(0);
			return;
		}

		int selRow = melodiiTableView->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = melodiiTableView->model()->index(selRow, 0);
		auto cel1Index = melodiiTableView->model()->index(selRow, 1);
		auto cel3Index = melodiiTableView->model()->index(selRow, 3);

		auto id = melodiiTableView->model()->data(cel0Index).toInt();
		auto titlu = melodiiTableView->model()->data(cel1Index).toString();
		auto rank = melodiiTableView->model()->data(cel3Index).toInt();

		titluTxt->setText(titlu);
		rankSlider->setValue(rank);
		idSelectat = id;
		});
}

void GUI::connectBtnUpdate()
{
	QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {

		try {

			auto titlu = titluTxt->text().toStdString();
			auto rank = rankSlider->value();

			srv.modifica(idSelectat, titlu, rank);
			reloadData();
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Eroare repo", e.what());
		}

		});
}

void GUI::connectBtnSterge()
{
	QObject::connect(btnSterge, &QPushButton::clicked, [&]() {

		try {

			int id = idSelectat;
			if (id == -1) {
				return;
			}

			srv.sterge(id);
			reloadData();
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Eroare repo", e.what());
		}

		});
}

