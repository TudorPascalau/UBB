#pragma once

#include <QtWidgets/QWidget>
#include "Service.h"
#include "MelodieTableModel.h"
#include "BarWidget.h"

#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

class GUI : public QWidget
{
    Q_OBJECT

    Service& srv;
    int idSelectat = -1;

    MelodieTableModel* melodiiTableModel;
    QTableView* melodiiTableView;
    BarWidget* barWidget;

    QLineEdit* titluTxt;
    QSlider* rankSlider;
    QPushButton* btnUpdate;
    QPushButton* btnSterge;

    QVBoxLayout* fullLayout;
    QHBoxLayout* topLayout;
    QVBoxLayout* leftLayout;

    void initGUI();
    void connectSignals();
    void reloadData();

    void createTable();
    void createLeftLayout();
    void createTopLayout();
    void createFullLayout();

    void connectTableSelection();
    void connectBtnUpdate();
    void connectBtnSterge();

public:
    GUI(Service& srv, QWidget *parent = nullptr);
    ~GUI();
};

