#pragma once

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "Service.h"
#include "TaskTableModel.h"

class StateWindow : public QWidget {
private:
    Service& srv;
    TaskTableModel* sourceModel;
    QSortFilterProxyModel* proxyModel;

    string stare;

    QTableView* table = new QTableView;
    QPushButton* btnOpen = new QPushButton{ "Open" };
    QPushButton* btnInprogress = new QPushButton{ "Inprogress" };
    QPushButton* btnClose = new QPushButton{ "Close" };

    void initGUI();
    void connectSignals();
    void changeSelectedTaskState(const string& newState);

public:
    StateWindow(Service& srv, TaskTableModel* sourceModel, const string& stare, QWidget* parent = nullptr);
};