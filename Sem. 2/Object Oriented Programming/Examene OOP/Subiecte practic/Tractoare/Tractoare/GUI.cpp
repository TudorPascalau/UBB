#include "GUI.h"

#include <QMessageBox>
#include <QDebug>

GUI::GUI(Service& service, QWidget* parent) : QWidget(parent), service{ service }
{
	initGUI();
	connectSignals();
	reloadData();
}

void GUI::initGUI()
{
	createTableView();
	createAddForm();
	createSideLayout();
	createTopLayout();
	createFullLayout();

	setWindowTitle("Tractoare");
	resize(1300, 800);
}

void GUI::connectSignals()
{
	connectAddButton();
	connnectCombo();
	connectTableSelect();
	connectWheelClick();
}

void GUI::reloadData()
{
	int prevId = lastSelectedId;
	if (prevId == -1) {
		auto prevIndexes = tableView->selectionModel()->selectedRows();
		if (!prevIndexes.isEmpty()) {
			prevId = tableModel->index(prevIndexes.at(0).row(), 0).data().toInt();
		}
	}

	tableModel->setTractoare(service.getSortatDenumire());
	reloadCombo();

	bool restored = false;
	if (prevId != -1) {
		for (int r = 0; r < tableModel->rowCount(); ++r) {
			if (tableModel->index(r, 0).data().toInt() == prevId) {
				tableView->selectRow(r);
				int nrRoti = tableModel->index(r, 3).data().toInt();
				wheelsWidget->setNrRoti(nrRoti);
				restored = true;
				break;
			}
		}
	}

	if (!restored && tableModel->rowCount() > 0) {
		tableView->selectRow(0);
		int nrRoti = tableModel->index(0, 3).data().toInt();
		wheelsWidget->setNrRoti(nrRoti);
	}

	if (!comboTip->currentText().isEmpty()) {
		tableModel->setTipSelectat(comboTip->currentText().toStdString());
	}
}

void GUI::reloadCombo()
{
	QString current = comboTip->currentText();
	comboTip->clear();

	auto tipuri = service.getTipuri();
	for (const auto& tip : tipuri) {
		comboTip->addItem(QString::fromStdString(tip));
	}

	if (!current.isEmpty()) {
		int idx = comboTip->findText(current);
		if (idx != -1) {
			comboTip->setCurrentIndex(idx);
		}
	}
}


void GUI::readForm(int& id, string& denumire, string& tip, int& nrRoti) const
{
	bool ok;
	id = idEdit->text().toInt(&ok);
	if (!ok) {
		throw ValidatorException("Id invalid! ");
	}

	denumire = denumireEdit->text().toStdString();
	tip = tipEdit->text().toStdString();

	nrRoti = nrRotiEdit->text().toInt(&ok);
	if (!ok) {
		throw ValidatorException("Numar de roti invalid! ");
	}

}

void GUI::createTableView()
{
	tableView = new QTableView{ this };
	tableModel = new TableModel{ this };

	tableView->setModel(tableModel);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void GUI::createAddForm()
{
	idEdit = new QLineEdit{ this };
	denumireEdit = new QLineEdit{ this };
	tipEdit = new QLineEdit{ this };
	nrRotiEdit = new QLineEdit{ this };
	btnAdd = new QPushButton{ "Adauga", this };
	addFormLayout = new QFormLayout;

	addFormLayout->addRow("ID:", idEdit);
	addFormLayout->addRow("Denumire:", denumireEdit);
	addFormLayout->addRow("Tip:", tipEdit);
	addFormLayout->addRow("Nr roti:", nrRotiEdit);
	addFormLayout->addWidget(btnAdd);
}

void GUI::createSideLayout()
{
	comboTip = new QComboBox{ this };

	sideLayout = new QVBoxLayout;
	sideLayout->addLayout(addFormLayout);
	sideLayout->addWidget(comboTip);
	sideLayout->addStretch();
}

void GUI::createTopLayout()
{
	topLayout = new QHBoxLayout;
	topLayout->addWidget(tableView, 3);
	topLayout->addLayout(sideLayout, 1);
}

void GUI::createFullLayout()
{
	wheelsWidget = new WheelsWidget{ this };
	
	fullLayout = new QVBoxLayout;
	fullLayout->addLayout(topLayout, 3);
	fullLayout->addWidget(wheelsWidget, 1);

	setLayout(fullLayout);
}

void GUI::connectAddButton()
{

	QObject::connect(btnAdd, &QPushButton::clicked, [&]{

		int id, nrRoti;
		string denumire, tip;

		try {
			readForm(id, denumire, tip, nrRoti);
		}
		catch (ValidatorException& e) {
			QMessageBox::warning(this, "Eroare GUI", e.what());
		}

		try {
			service.addTractor(id, denumire, tip, nrRoti);
		}
		catch (ValidatorException& e) {
			QMessageBox::warning(this, "Eroare validator", e.what());
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Eroare repo", e.what());
		}

		reloadData();
	});


}

void GUI::connnectCombo()
{
	QObject::connect(comboTip, &QComboBox::currentTextChanged, [&]() {
		tableModel->setTipSelectat(comboTip->currentText().toStdString());
	});
}

void GUI::connectTableSelect()
{
	QObject::connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {

		auto indexes = tableView->selectionModel()->selectedRows();

		if (indexes.isEmpty())
			return;

		int row = indexes.at(0).row();
		
		int id = tableModel->index(row, 0).data().toInt();
		int nrRoti = tableModel->index(row, 3).data().toInt();

		wheelsWidget->setNrRoti(nrRoti);
		tableModel->setIdSelectat(id);

	});
}

void GUI::connectWheelClick()
{
	QObject::connect(wheelsWidget, &WheelsWidget::wheelClicked, [&]() {
		int id = tableModel->getIdSelectat();
		
		try {
			service.decrementRoti(id);
		}
		catch (RepoException& e) {
			QMessageBox::warning(this, "Eroare repo", e.what());
		}

		reloadData();
	});
}

void WheelsWidget::paintEvent(QPaintEvent*)
{
	QPainter p{ this };
	int r = 20;
	int x = 20;
	int y = height() / 2 - r;

	for (int i = 0; i < nrRoti; i++) {
		p.drawEllipse(x, y, 2 * r, 2 * r);
		x = x + 2 * r + 10;
	}
}

void WheelsWidget::mousePressEvent(QMouseEvent* ev)
{
	int r = 20;
	int x = 20;
	int y = height() / 2 - r;

	for (int i = 0; i < nrRoti; i++) {
		QRect cerc{ x, y, 2 * r, 2 * r };

		if (cerc.contains(ev->pos())) {
			emit wheelClicked();
			return;
		}

		x = x + 2 * r + 10;
	}
}
