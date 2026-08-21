#pragma once
#include "Service.h"
#include "XOTableModel.h"

#include <QtWidgets/QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class GUI : public QWidget
{
    Q_OBJECT

    Service& srv;
    int idSelect = -1;
    
    QTableView* xoView;
    XOTableModel* xoModel;

    QLineEdit* dimTxt;
    QLineEdit* tableTxt;
    QLineEdit* playerTxt;
    QLineEdit* stareTxt;

    QPushButton* btnAdd;
    QPushButton* btnModifica;

    QWidget* boardWidget;
    QGridLayout* boardLayout;
    vector<QPushButton*> boardButtons;

    QVBoxLayout* sideLayout;
    QHBoxLayout* topLayout;
    QVBoxLayout* mainLayout;
    

    void initGUI();
    void connectSignals();
    void reloadData();

    void clearBoard();
    void reloadBoard(const XO& xo);

    void createTable();
    void createSideLayout();
    void createTopLayout();
    void createGameLayout();
    void createMainLayout();

    void connectAddButton();
    void connectTableSelect();
    void connectBtnModifica();

public:
    GUI(Service& srv, QWidget *parent = nullptr);
    ~GUI();
};

