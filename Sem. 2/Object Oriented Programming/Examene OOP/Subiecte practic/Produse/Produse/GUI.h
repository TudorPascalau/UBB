#pragma once

#include <QtWidgets/QWidget>
#include "Service.h"
#include "ProdusTableModel.h"
#include <ProductWindow.h>

#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

class GUI : public QWidget
{
    Q_OBJECT

    Service& srv;

    QTableView* produsView;
    ProdusTableModel* produsModel;

    map<string, ProductWindow*> windows;

    QLineEdit* idTxt;
    QLineEdit* numeTxt;
    QLineEdit* tipTxt;
    QLineEdit* pretTxt;
    QPushButton* btnAdd;
    QSlider* slidePret;

    QHBoxLayout* mainLayout;
    QVBoxLayout* sideLayout;

    void initGUI();
    void connectSignals();
    void reloadData();
    void reloadWindows();

    void createTable();
    void createSideLayout();
    void createMainLayout();

    void readForms(int &id, string& nume, string& tip, double& pret);
    void connectBtnAdd();
    void connectSlidePret();


public:
    GUI(Service& srv, QWidget *parent = nullptr);
    ~GUI();

};

