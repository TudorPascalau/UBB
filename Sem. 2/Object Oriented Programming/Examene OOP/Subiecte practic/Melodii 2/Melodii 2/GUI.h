#pragma once

#include <QtWidgets/QWidget>
#include "Service.h"
#include "MelodieTableModel.h"
#include "CircleWidget.h"

#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class GUI : public QWidget
{
    Q_OBJECT

    Service& srv;
    int idSelected = -1;

    QTableView* melodiiView;
    MelodieTableModel* melodiiModel;

    QLineEdit* titluTxt;
    QLineEdit* artistTxt;
    QLineEdit* genTxt;
    QPushButton* btnAdauga;
    QPushButton* btnSterge;

    CircleWidget* popWidget;
    CircleWidget* rockWidget;
    CircleWidget* folkWidget;
    CircleWidget* discoWidget;

    QHBoxLayout* topLayout;
    QVBoxLayout* leftLayout;
    QGridLayout* mainLayout;

    void initGUI();
    void connectSignals();
    void reloadData();
    void reloadCircles();

    void createTable();
    void createLeftLayout();
    void createTopLayout();
    void createMainLayout();

    void connectBtnAdauga();
    void connectTableSelection();
    void connectBtnSterge();

public:
    GUI(Service& srv, QWidget *parent = nullptr);
    ~GUI();

private:
};

