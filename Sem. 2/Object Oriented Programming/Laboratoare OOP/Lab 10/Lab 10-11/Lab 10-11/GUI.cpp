#include "GUI.h"

#include <QMessageBox>
#include <QLabel>
#include <QPainter>
#include <QRandomGenerator>

GUI::GUI(Service& srv, QWidget* parent) : QWidget(parent), srv(srv)
{
	initGUI();
	connectSignals();
	loadData();
}

void GUI::initGUI()
{
	createTable();
	createList();
	createCRUDWidgets();
	createDisplayWidgets();
	createMainLayout();

	setWindowTitle("Biblioteca");
	resize(1300, 600);
}

void GUI::connectSignals()
{
	connectTableSelection();
	connectAddButton();
	connectDeleteButton();
	connectUpdateButton();
	connectClearButton();
	connectUndoButton();
	connectDisplayButton();
	connectFilterButton();
	connectSortButton();

	connectAddCosMainButton();
	connectDeleteCosMainButton();
	connectGenerateCosMainButton();
	connectCosCrudButton();
	connectCosReadOnlyButton();
}

void GUI::loadData()
{
	modelCarti->setCarti(srv.getAll());
	loadRaport();

	/*listaCarti->clear();
	for (auto& carte : carti) {
		string id = std::to_string(carte.getId());
		string titlu = carte.getTitlu();
		string autor = carte.getAutor();
		string an = std::to_string(carte.getAn());
		string gen = carte.getGen();
		string itemText = id + " - " + titlu + " - " + autor + " - " + an + " - " + gen;
		listaCarti->addItem(QString::fromStdString(itemText));
	}*/

	loadRaport();
}

void GUI::loadData(const Lista<int>& pozitii)
{
	modelCarti->setCarti(srv.getAll(), pozitii);

	/*listaCarti->clear();
	for(const int poz : pozitii) {
		const Carte& carte = carti.get(poz);
		string id = std::to_string(carte.getId());
		string titlu = carte.getTitlu();
		string autor = carte.getAutor();
		string an = std::to_string(carte.getAn());
		string gen = carte.getGen();
		string itemText = id + " - " + titlu + " - " + autor + " - " + an + " - " + gen;
		listaCarti->addItem(QString::fromStdString(itemText));
	}*/
}

void GUI::loadRaport()
{
	while (QLayoutItem* item = layoutRaport->takeAt(0)) {
		if (QWidget* widget = item->widget())
			delete widget;
		delete item;
	}

	const Lista<DTORaport> raport = srv.raportGen();
	for (const auto& dto : raport) {
		const string gen = dto.getGen();
		const int count = dto.getCount();

		auto btnRaport = new QPushButton(QString::fromStdString(gen));

		QObject::connect(btnRaport, &QPushButton::clicked, [this, gen, count]() {
			QMessageBox::information(
				this,
				"Raport",
				QString("Exista %1 carti de tip %2").arg(count).arg(gen));
		});

		layoutRaport->addWidget(btnRaport);
	
	}

}

bool GUI::readForm(int& id, string& titlu, string& autor, int& an, string& gen)
{
	bool ok = false;
	id = txtId->text().toInt(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Eroare", "Id-ul trebuie sa fie numar.");
		return false;
	}
	titlu = txtTitlu->text().toStdString();
	autor = txtAutor->text().toStdString();
	an = txtAn->text().toInt(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Eroare", "Anul trebuie sa fie numar.");
		return false;
	}
	gen = txtGen->text().toStdString();
	return true;
}

void GUI::clearForm()
{
	txtId->clear();
	txtTitlu->clear();
	txtAutor->clear();
	txtAn->clear();
	txtGen->clear();
	txtFilter->clear();
}

void GUI::createTable()
{
	tableCarti = new QTableView;
	modelCarti = new CartiTableModel{ this };

	tableCarti->setModel(modelCarti);

	tableCarti->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableCarti->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableCarti->setSelectionMode(QAbstractItemView::SingleSelection);
	tableCarti->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void GUI::createList() 
{
	//listaCarti = new QListWidget;
}

QFormLayout* GUI::createFormLayout()
{
	auto formLayout = new QFormLayout;
	formLayout->addRow("Id:", txtId);
	formLayout->addRow("Titlu:", txtTitlu);
	formLayout->addRow("Autor:", txtAutor);
	formLayout->addRow("An:", txtAn);
	formLayout->addRow("Gen:", txtGen);
	return formLayout;
}

void GUI::createCRUDWidgets()
{
	txtId = new QLineEdit;
	txtTitlu = new QLineEdit;
	txtAutor = new QLineEdit;
	txtAn = new QLineEdit;
	txtGen = new QLineEdit;

	btnAdauga = new QPushButton("Adauga");
	btnSterge = new QPushButton("Sterge");
	btnModifica = new QPushButton("Modifica");
	btnClear = new QPushButton("Clear");
	btnUndo = new QPushButton("Undo");
}

void GUI::createDisplayWidgets()
{
	txtFilter = new QLineEdit;

	btnAfiseaza = new QPushButton("Afiseaza");
	btnFiltreaza = new QPushButton("Filtreaza");
	btnSortare = new QPushButton("Sortare");

	comboFiltrare = new QComboBox;
	comboFiltrare->addItems({ "Titlu", "An" });

	comboSortare = new QComboBox;
	comboSortare->addItems({ "Titlu", "Autor", "An + Gen" });

	btnAdaugaCosMain = new QPushButton("Adauga in cos");
	btnStergeCosMain = new QPushButton("Sterge din cos");
	btnGenereazaCosMain = new QPushButton("Genereaza cos");
	btnCosCrud = new QPushButton("Deschide CosCRUDGUI");
	btnCosReadOnly = new QPushButton("Deschide CosReadOnly");	

	spinNrCartiCosMain = new QSpinBox;
	spinNrCartiCosMain->setMinimum(1);
	spinNrCartiCosMain->setMaximum(100);
}

QHBoxLayout* GUI::createCRUDWidgetsLayout()
{
	auto btnLayout = new QHBoxLayout;
	btnLayout->addWidget(btnAdauga);
	btnLayout->addWidget(btnSterge);
	btnLayout->addWidget(btnModifica);
	btnLayout->addWidget(btnUndo);
	btnLayout->addWidget(btnClear);
	return btnLayout;
}

QVBoxLayout* GUI::createDisplayWidgetsLayout()
{
	auto displayLayout = new QVBoxLayout;
	displayLayout->addWidget(btnAfiseaza);

	auto filterLayout = new QHBoxLayout;
	filterLayout->addWidget(new QLabel("Filtreaza dupa:"));
	filterLayout->addWidget(comboFiltrare, 1);
	filterLayout->addWidget(txtFilter, 1);
	filterLayout->addWidget(btnFiltreaza, 1);

	auto sortLayout = new QHBoxLayout;
	sortLayout->addWidget(new QLabel("Sorteaza dupa:"));
	sortLayout->addWidget(comboSortare, 1);
	sortLayout->addWidget(btnSortare, 1);

	displayLayout->addLayout(filterLayout);
	displayLayout->addLayout(sortLayout);

	auto cosLayout = new QHBoxLayout;
	cosLayout->addWidget(btnAdaugaCosMain);
	cosLayout->addWidget(btnStergeCosMain);
	cosLayout->addWidget(new QLabel("Nr:"));
	cosLayout->addWidget(spinNrCartiCosMain);
	cosLayout->addWidget(btnGenereazaCosMain);

	displayLayout->addLayout(cosLayout);
	displayLayout->addWidget(btnCosCrud);
	displayLayout->addWidget(btnCosReadOnly);

	return displayLayout;
}

QHBoxLayout* GUI::createCartiLayout() {
	auto cartiLayout = new QHBoxLayout;
	cartiLayout->addWidget(tableCarti);
	//cartiLayout->addWidget(listaCarti);
	return cartiLayout;
}

QVBoxLayout* GUI::createLeftLayout()
{
	auto leftLayout = new QVBoxLayout;
	leftLayout->addLayout(createCartiLayout(), 1);
	leftLayout->addLayout(createDisplayWidgetsLayout());
	return leftLayout;
}

QVBoxLayout* GUI::createRightLayout()
{
	auto rightLayout = new QVBoxLayout;
	rightLayout->addLayout(createFormLayout());
	rightLayout->addLayout(createCRUDWidgetsLayout());

	layoutRaport = new QVBoxLayout;
	rightLayout->addWidget(new QLabel("Raport genuri"));
	rightLayout->addLayout(layoutRaport);

	rightLayout->addStretch();
	return rightLayout;
}

void GUI::createMainLayout()
{
	layout = new QHBoxLayout;

	layout->addLayout(createLeftLayout(), 3);
	layout->addLayout(createRightLayout(), 1);

	setLayout(layout);
}

void GUI::connectTableSelection()
{
	QObject::connect(tableCarti->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		const auto index = tableCarti->currentIndex();
		if (!index.isValid()) {
			return;
		}

		const Carte& carte = modelCarti->getCarte(index.row());

		txtId->setText(QString::number(carte.getId()));
		txtTitlu->setText(QString::fromStdString(carte.getTitlu()));
		txtAutor->setText(QString::fromStdString(carte.getAutor()));
		txtAn->setText(QString::number(carte.getAn()));
		txtGen->setText(QString::fromStdString(carte.getGen()));
		});
}

void GUI::connectAddButton()
{
	QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {
		int id, an;
		string titlu, autor, gen;

		if(!readForm(id, titlu, autor, an, gen))
			return;

		try {
			srv.addCarte(id, titlu, autor, gen, an);
			loadData();
			clearForm();
		}
		catch (const ValidationError& ve) {
			QMessageBox::warning(this, "Eroare validare", QString::fromStdString(ve.getMessage()));
		}
		catch (const RepoError& re) {
			QMessageBox::warning(this, "Eroare repo", QString::fromStdString(re.getMessage()));
		}

	});
}

void GUI::connectDeleteButton()
{
	QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
		bool ok = false;
		const int id = txtId->text().toInt(&ok);

		if (!ok) {
			QMessageBox::warning(this, "Eroare", "Id-ul trebuie sa fie numar.");
			return;
		}

		try {
			srv.deleteCarte(id);
			loadData();
			clearForm();
		}

		catch (const RepoError& re) {
			QMessageBox::warning(this, "Eroare repo", QString::fromStdString(re.getMessage()));
		}
	});
}

void GUI::connectUpdateButton()
{
	QObject::connect(btnModifica, &QPushButton::clicked, [&]() {
		int id, an;
		string titlu, autor, gen;

		if(!readForm(id, titlu, autor, an, gen))
			return;

		try {
			srv.updateCarte(id, titlu, autor, gen, an);
			loadData();
			clearForm();
		}
		catch (const ValidationError& ve) {
			QMessageBox::warning(this, "Eroare validare", QString::fromStdString(ve.getMessage()));
		}
		catch (const RepoError& re) {
			QMessageBox::warning(this, "Eroare repo", QString::fromStdString(re.getMessage()));
		}
	});
}

void GUI::connectUndoButton() {
	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			loadData();
			clearForm();
		}
		catch (const RepoError& re) {
			QMessageBox::warning(this, "Eroare repo", QString::fromStdString(re.getMessage()));
		}
	});
}

void GUI::connectClearButton()
{
	QObject::connect(btnClear, &QPushButton::clicked, [&]() {
		clearForm();
		tableCarti->clearSelection();
	});
}

void GUI::connectDisplayButton()
{
	QObject::connect(btnAfiseaza, &QPushButton::clicked, [&]() {
		loadData();
		});
}

void GUI::connectFilterButton()
{
	QObject::connect(btnFiltreaza, &QPushButton::clicked, [&]() {
		const QString criteriu = comboFiltrare->currentText();
		const QString valoare = txtFilter->text();

		if (valoare.isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Campul de filtrare nu poate fi gol.");
			return;
		}

		if (criteriu == "Titlu") {
			loadData(srv.filterByTitlu(valoare.toStdString()));
		}

		else if (criteriu == "An") {
			bool ok = false;
			const int an = valoare.toInt(&ok);
			if (!ok) {
				QMessageBox::warning(this, "Eroare", "Anul trebuie sa fie numar.");
				return;
			}
			loadData(srv.filterByAn(an));
		}

	});
}

void GUI::connectSortButton()
{
	QObject::connect(btnSortare, &QPushButton::clicked, [&]() {
		const QString criteriu = comboSortare->currentText();

		if (criteriu == "Titlu") {
			loadData(srv.sortByTitlu());
		}
		else if (criteriu == "Autor") {
			loadData(srv.sortByAutor());
		}
		else if (criteriu == "An + Gen") {
			loadData(srv.sortByAnGen());
		}
	});
}

// GUI.cpp
void GUI::connectAddCosMainButton()
{
	QObject::connect(btnAdaugaCosMain, &QPushButton::clicked, [&]() {
		const QString titlu = txtTitlu->text();

		if (titlu.isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Selectati o carte sau introduceti titlul.");
			return;
		}

		try {
			srv.adaugaCos(titlu.toStdString());
		}
		catch (const RepoError& re) {
			QMessageBox::warning(this, "Eroare repo", QString::fromStdString(re.getMessage()));
		}
		});
}

void GUI::connectDeleteCosMainButton()
{
	QObject::connect(btnStergeCosMain, &QPushButton::clicked, [&]() {
		bool ok = false;
		const int id = txtId->text().toInt(&ok);

		if (!ok) {
			QMessageBox::warning(this, "Eroare", "Selectati o carte sau introduceti id-ul.");
			return;
		}

		srv.stergeCos(id);
		});
}

void GUI::connectGenerateCosMainButton()
{
	QObject::connect(btnGenereazaCosMain, &QPushButton::clicked, [&]() {
		try {
			srv.genereazaCos(spinNrCartiCosMain->value());
		}
		catch (const RepoError& re) {
			QMessageBox::warning(this, "Eroare repo", QString::fromStdString(re.getMessage()));
		}
		});
}

void GUI::connectCosCrudButton()
{
	QObject::connect(btnCosCrud, &QPushButton::clicked, [&]() {
		auto cosWindow = new CosCrudGUI(srv);
		cosWindow->setAttribute(Qt::WA_DeleteOnClose);
		cosWindow->show();
		});
}

void GUI::connectCosReadOnlyButton()
{
	QObject::connect(btnCosReadOnly, &QPushButton::clicked, [&]() {
		auto cosWindow = new CosReadOnlyGUI(srv);
		cosWindow->setAttribute(Qt::WA_DeleteOnClose);
		cosWindow->show();
	});
}


// --- CosCrudGUI ---

CosCrudGUI::CosCrudGUI(Service& srv, QWidget* parent) : QWidget(parent), srv(srv)
{
	srv.getCosCarti().addObserver(this);
	initGUI();
	connectSignals();
	loadCos();
}

CosCrudGUI::~CosCrudGUI()
{
	srv.getCosCarti().removeObserver(this);
}

void CosCrudGUI::initGUI()
{
	createTable();
	createCosWidgets();
	createMainLayout();

	setWindowTitle("Cos CRUD");
	resize(900, 450);
}

void CosCrudGUI::loadCos()
{
	std::vector<Carte> cartiCos;

	for (const int id : srv.getCos()) {
		try {
			cartiCos.push_back(srv.findCarte(id));
		}
		catch (const RepoError&) {
		}
	}

	modelCos->setCarti(cartiCos);
}

void CosCrudGUI::createTable()
{
	tableCos = new QTableView;
	modelCos = new CartiTableModel{ this };

	tableCos->setModel(modelCos);
	tableCos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableCos->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableCos->setSelectionMode(QAbstractItemView::SingleSelection);
	tableCos->setSelectionBehavior(QAbstractItemView::SelectRows);
}

QVBoxLayout* CosCrudGUI::createLeftLayout()
{
	auto leftLayout = new QVBoxLayout;
	leftLayout->addWidget(tableCos);
	return leftLayout;
}

void CosCrudGUI::createMainLayout()
{
	auto mainLayout = new QHBoxLayout;
	mainLayout->addLayout(createLeftLayout(), 3);
	mainLayout->addLayout(createRightLayout(), 1);

	setLayout(mainLayout);
}

void CosCrudGUI::update()
{
	loadCos();
}

void CosCrudGUI::connectSignals()
{
	connectGenereazaButton();
	connectGolesteButton();
}

void CosCrudGUI::createCosWidgets()
{
	spinNrCarti = new QSpinBox;
	spinNrCarti->setMinimum(1);
	spinNrCarti->setMaximum(100);

	btnGenereazaCos = new QPushButton("Genereaza cos");
	btnGolesteCos = new QPushButton("Goleste cos");
}

QVBoxLayout* CosCrudGUI::createRightLayout()
{
	auto rightLayout = new QVBoxLayout;
	rightLayout->addWidget(new QLabel("Numar carti:"));
	rightLayout->addWidget(spinNrCarti);
	rightLayout->addWidget(btnGenereazaCos);
	rightLayout->addWidget(btnGolesteCos);
	rightLayout->addStretch();
	return rightLayout;
}

void CosCrudGUI::connectGenereazaButton()
{
	QObject::connect(btnGenereazaCos, &QPushButton::clicked, [&]() {
		try {
			srv.genereazaCos(spinNrCarti->value());
		}
		catch (const RepoError& re) {
			QMessageBox::warning(this, "Eroare repo", QString::fromStdString(re.getMessage()));
		}
	});
}

void CosCrudGUI::connectGolesteButton()
{
	QObject::connect(btnGolesteCos, &QPushButton::clicked, [&]() {
		srv.golesteCos();
		});
}

// -- CosReadOnlyGUI --

CosReadOnlyGUI::CosReadOnlyGUI(Service& srv, QWidget* parent) : QWidget(parent), srv(srv) {
	srv.getCosCarti().addObserver(this);
	setWindowTitle("Cos Read Only");
	resize(650, 450);
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
	srv.getCosCarti().removeObserver(this);
}

void CosReadOnlyGUI::update(){
	repaint();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
	QWidget::paintEvent(ev);
	QPainter p{ this };

	p.setRenderHint(QPainter::Antialiasing);
	const int nrCarti = srv.sizeCos();

	p.setPen(Qt::white);
	p.setFont(QFont{ "Arial", 14, QFont::Bold });
	p.drawText(20, 30, QString("Numar carti in cos %1").arg(nrCarti));

	for (int i = 0; i < nrCarti; i++) {
		const int dim = QRandomGenerator::global()->bounded(30, 70);
		int maxX = 0, maxY = 0;
		if (width() > dim) maxX = width() - dim;
		else maxX = 1;

		if (height() > dim + 50) maxY = height() - dim - 50;
		else maxY = 1;

		const int x = QRandomGenerator::global()->bounded(maxX);
		const int y = QRandomGenerator::global()->bounded(maxY);

		const QColor color{
			QRandomGenerator::global()->bounded(256),
			QRandomGenerator::global()->bounded(256),
			QRandomGenerator::global()->bounded(256)

		};

		p.setBrush(color);
		p.setPen(Qt::black);

		if (i % 2 == 0) {
			p.drawEllipse(x, y, dim, dim);
		}
		else {
			p.drawRect(x, y, dim, dim);
		}
	}
}

