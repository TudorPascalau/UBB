#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPaintEvent>
#include <QTableView>

#include "Service.h"
#include "CartiTableModel.h"

class CosGUI;

class GUI : public QWidget
{
private:
	Service& srv;

	// Componente GUI
	QTableView* tableCarti = nullptr;
	CartiTableModel* modelCarti = nullptr;

	//QListWidget* listaCarti = nullptr;
	QHBoxLayout* layout = nullptr;
	QVBoxLayout* layoutRaport = nullptr;

	// Form inputs
	QLineEdit* txtId = nullptr;
	QLineEdit* txtTitlu = nullptr;
	QLineEdit* txtAutor = nullptr;
	QLineEdit* txtAn = nullptr;
	QLineEdit* txtGen = nullptr;

	QLineEdit* txtFilter = nullptr;

	// Butoane operatii CRUD
	QPushButton* btnAdauga = nullptr;
	QPushButton* btnSterge = nullptr;
	QPushButton* btnModifica = nullptr;
	QPushButton* btnClear = nullptr;
	QPushButton* btnUndo = nullptr;

	// Butoane pentru afisare, filtrare si sortare
	QPushButton* btnAfiseaza = nullptr;
	QPushButton* btnFiltreaza = nullptr;
	QPushButton* btnSortare = nullptr;

	QComboBox* comboFiltrare = nullptr;
	QComboBox* comboSortare = nullptr;

	//Widget-uri pentru cos
	QPushButton* btnAdaugaCosMain = nullptr;
	QPushButton* btnStergeCosMain = nullptr;
	QPushButton* btnGenereazaCosMain = nullptr;
	QPushButton* btnCosCrud = nullptr;
	QPushButton* btnCosReadOnly = nullptr;
	QSpinBox* spinNrCartiCosMain = nullptr;

	
	/*
	* Initializarea componentelor GUI
	* pre: srv este un service valid
	* post: componentele GUI sunt initializate, semnalele sunt conectate la sloturi si datele initiale sunt incarcate in tabel
	*/
	void initGUI();

	/*
	* Conectarea semnalelor la sloturi
	* pre: componentele GUI sunt initializate
	* post: semnalele generate de interactiunea cu componentele GUI sunt 
			conectate la sloturile corespunzatoare pentru a raspunde la actiunile utilizatorului
	*/
	void connectSignals();

	/*
	* Incarcarea datelor din service in tabel
	* pre: service-ul este valid
	* post: datele din service sunt afisate in tabel
	*/
	void loadData();

	/*
	* Incarcarea datelor in tabel folosind o lista de pozitii
	* pre: service-ul este valid, pozitii este o lista de pozitii valide in service
	* post: datele corespunzatoare pozitiilor din lista sunt afisate in tabel
	*/
	void loadData(const Lista<int>& pozitii);

	/**/
	void loadRaport();

	/*
	* Functie auxiliara pentru citirea datelor din campurile de input si validarea acestora
	* @param id, titlu, autor, an, gen: variabilele in care se vor stoca valorile citite din campurile de input
	* @return: true daca citirea si validarea au fost realizate cu succes, false altfel
	*/
	bool readForm(int& id, string& titlu, string& autor, int& an, string& gen);

	//Functie auxiliara pentru stergerea textului din campurile de input
	void clearForm();


	//Creaza tabelul pentru afisarea cartilor
	void createTable();

	//Creaza lista pentru afisarea cartilor
	void createList();

	/*
	* Creaza layout-ul pentru campurile de input
	* @return: un pointer la layout-ul creat pentru campurile de input
	*/
	QFormLayout* createFormLayout();

	// Creeaza widget-urile pentru operatii CRUD
	void createCRUDWidgets();

	// Creeaza widget-urile pentru afisare, filtrare si sortare
	void createDisplayWidgets();

	/*
	* Creaza layout-ul pentru butoane CRUD
	* @return: un pointer la layout-ul creat pentru butoane
	*/
	QHBoxLayout* createCRUDWidgetsLayout();

	/* 
	* Creaza layout-ul pentru butoanele de afisare, filtrare si sortare
	* @return: un pointer la layout-ul creat pentru butoanele de afisare, filtrare si sortare
	*/
	QVBoxLayout* createDisplayWidgetsLayout();

	/*
	* Creaza layout-ul pentru partea de carti, care contine tabelul si lista de carti
	* @return: un pointer la layout-ul creat pentru partea de carti
	*/
	QHBoxLayout* createCartiLayout();

	/*
	* Creaza layout-ul pentru partea stanga a ferestrei, care contine tabelul si lista de carti
	* @return: un pointer la layout-ul creat pentru partea stanga a ferestrei
	*/
	QVBoxLayout* createLeftLayout();

	/*
	* Creaza layout-ul pentru partea dreapta a ferestrei, care contine campurile de input si butoanele
	* @return: un pointer la layout-ul creat pentru partea dreapta a ferestrei
	*/
	QVBoxLayout* createRightLayout();

	// Creaza layout-ul principal al ferestrei, 
	// Imparte fereastra in doua: tabelul pe stanga si campurile de input + butoanele pe dreapta
	void createMainLayout();

	// Conecteaza semnalele generate de interactiunea cu tabelul si butoanele la sloturile corespunzatoare
	void connectTableSelection();
	void connectAddButton();
	void connectDeleteButton();
	void connectUpdateButton();
	void connectClearButton();
	void connectUndoButton();
	void connectDisplayButton();
	void connectFilterButton();
	void connectSortButton();

	void connectAddCosMainButton();
	void connectDeleteCosMainButton();
	void connectGenerateCosMainButton();
	void connectCosCrudButton();
	void connectCosReadOnlyButton();

public:
	/*
	* Constructorul clasei GUI
	* @param: srv: referinta la service-ul care va fi folosit pentru a accesa datele si logica aplicatiei
	*		  parent: pointer la widget-ul parinte, default nullptr
	* pre: srv este un service valid
	* post: un obiect GUI este creat, cu componentele GUI initializate, 
			semnalele conectate la sloturi si datele initiale incarcate in tabel
	*/
	explicit GUI(Service& srv, QWidget* parent = nullptr);
};

class CosCrudGUI : public QWidget,  public Observer
{
private:
	Service& srv;

	QTableView* tableCos = nullptr;
	CartiTableModel* modelCos = nullptr;

	QSpinBox* spinNrCarti = nullptr;

	QPushButton* btnGenereazaCos = nullptr;
	QPushButton* btnGolesteCos = nullptr;

	void initGUI();
	void connectSignals();
	void loadCos();

	void createTable();
	void createCosWidgets();

	QVBoxLayout* createLeftLayout();
	QVBoxLayout* createRightLayout();
	void createMainLayout();

	void connectGenereazaButton();
	void connectGolesteButton();

public:
	explicit CosCrudGUI(Service& srv, QWidget* parent = nullptr);
	~CosCrudGUI() override;

	void update() override;
};

class CosReadOnlyGUI : public QWidget, public Observer {
private:
	Service& srv;

public:
	explicit CosReadOnlyGUI(Service& srv, QWidget* parent = nullptr);
	~CosReadOnlyGUI() override;

	void update() override;

protected:
	void paintEvent(QPaintEvent* ev) override;
};
