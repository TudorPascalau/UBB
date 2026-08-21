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

    void initGUI();
    void connectSignals();
    void reloadData();

    void createTable();
    void createSideLayout();
    void createMainLayout();

    void connectAdd();
    void connectFilter();

public:
    GUI(Service& srv, QWidget *parent = nullptr);
    ~GUI();
};

