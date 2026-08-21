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

    /*
    * Metoda ce initializeaza fereastra
    * Post: Fereastra este creata, widget-uri adaugate si apoi afisatea
    */
    void initGUI();

    /*
    * Metoda ce conecteaza butoanele de schimbare stare
    */
    void connectSignals();

    /*
    * Metoda ce schimba starea task-ului selectat
    * @param newState: starea noua in care schimbam
    */
    void changeSelectedTaskState(const string& newState);

public:

    /*
    * Constructor pentru ferestrele specifice starii task-ului
    * @param srv: service asociat interfetei grafice
    * @param sourceModel: modelul de baza din care luam informatiile
    * @param stare: starea dupa care filtram
    * Post: fereastra este initializata, conectata si afisata
    */
    StateWindow(Service& srv, TaskTableModel* sourceModel, const string& stare, QWidget* parent = nullptr);
};