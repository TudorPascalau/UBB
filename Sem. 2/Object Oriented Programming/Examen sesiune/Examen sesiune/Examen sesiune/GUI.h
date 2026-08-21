#pragma once
#include <QtWidgets/QWidget>
#include "Service.h"
#include "TaskTableModel.h"
#include "StateWindow.h"

#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class GUI : public QWidget
{
    Q_OBJECT

    Service& srv;

    QTableView* taskView;
    TaskTableModel* taskModel;

    StateWindow* openWindow;
    StateWindow* inprogressWindow;
    StateWindow* closedWindow;

    QVBoxLayout* sideLy;
    QHBoxLayout* mainLy;

    QLabel* idLbl;
    QLabel* descLbl;
    QLabel* progLbl;
    QLabel* stareLbl;

    QLineEdit* idTxt;
    QLineEdit* descTxt;
    QLineEdit* progTxt;
    QLineEdit* stareTxt;

    QPushButton* btnAdd;

    QLabel* nameLbl;
    QLineEdit* nameFilter;

    /*
    * Metoda ce initializeaza componentele interfetei grafice
    */
    void initGUI();

    /*
    * Metoda ce coneteaza semnalele si sloturile folosite in interfata grafica
    */
    void connectSignals();

    /*
    * Metoda ce incarca informatiile din model in view
    */
    void reloadData();

    /*
    * Metoda ce creeaza elementele ce tin de tabelul principal
    */
    void createTable();

    /*
    * Metoda ce creeaza elementele ce tin de interactiune utilizator
    */
    void createSideLayout();

    /*
    * Metoda ce creeaza layout-ul principal
    */
    void createMainLayout();

    /*
    * Metoda ce conecteaza butonul de adaugare Task
    */
    void connectAdd();

    /*
    * Metoda ce conecteaza filtrul dupa nume programator
    */
    void connectFilter();

public:
    /*
    * Constructor pentru interfata grafica
    * @param srv: service asociat interfetei grafice
    * Post: interfata grafica e initializata, conectata si afisata
    */
    GUI(Service& srv, QWidget* parent = nullptr);
    ~GUI();
};

