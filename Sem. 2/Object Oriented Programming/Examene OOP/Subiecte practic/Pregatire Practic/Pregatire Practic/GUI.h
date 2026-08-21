// === GUI.h ===
#pragma once
#include "Service.h"
#include "ProdusTableModel.h"

#include <QAbstractItemView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>

class GUI : public QWidget {
    Q_OBJECT

        Service& srv;
    int selectedId = -1;

    QTableView* table = nullptr;
    ProdusTableModel* model = nullptr;

    QLineEdit* idTxt = nullptr;
    QLineEdit* numeTxt = nullptr;
    QLineEdit* tipTxt = nullptr;
    QLineEdit* pretTxt = nullptr;
    QPushButton* btnAdd = nullptr;
    QPushButton* btnUpdate = nullptr;

    void initGUI();
    void connectSignals();
    void reloadData();

public:
    explicit GUI(Service& srv, QWidget* parent = nullptr)
        : QWidget(parent), srv{ srv } {
        initGUI();
        connectSignals();
        reloadData();
    }
};

// === GUI.cpp ===
#include "GUI.h"

void GUI::initGUI() {
    table = new QTableView{ this };
    model = new ProdusTableModel{ this };
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows); // selecteaza randul intreg
    table->setSelectionMode(QAbstractItemView::SingleSelection); // o singura selectie

    auto* formLy = new QVBoxLayout;
    idTxt = new QLineEdit{ this };
    numeTxt = new QLineEdit{ this };
    tipTxt = new QLineEdit{ this };
    pretTxt = new QLineEdit{ this };
    btnAdd = new QPushButton{ "Adauga", this };
    btnUpdate = new QPushButton{ "Modifica", this };

    formLy->addWidget(new QLabel{ "Id", this });       formLy->addWidget(idTxt);
    formLy->addWidget(new QLabel{ "Nume", this });     formLy->addWidget(numeTxt);
    formLy->addWidget(new QLabel{ "Tip", this });      formLy->addWidget(tipTxt);
    formLy->addWidget(new QLabel{ "Pret", this });     formLy->addWidget(pretTxt);
    formLy->addWidget(btnAdd);
    formLy->addWidget(btnUpdate);
    formLy->addStretch();

    auto* mainLy = new QHBoxLayout;
    mainLy->addWidget(table);
    mainLy->addLayout(formLy);
    setLayout(mainLy);
    resize(1000, 600);
}

void GUI::reloadData() {
    model->setElems(srv.getAll()); // orice modificare in service se reflecta in tabel
    table->clearSelection();
    selectedId = -1;
}

void GUI::connectSignals() {
    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        try {
            bool okId = false;
            bool okPret = false;
            int id = idTxt->text().toInt(&okId);
            double pret = pretTxt->text().toDouble(&okPret);
            if (!okId || !okPret) {
                throw ValidatorException{ "Id/Pret invalid!" };
            }
            srv.adauga(id, numeTxt->text().toStdString(), tipTxt->text().toStdString(), pret);
            reloadData();
        }
        catch (const exception& ex) {
            QMessageBox::warning(this, "Eroare", ex.what());
        }
        });

    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        const auto indexes = table->selectionModel()->selectedIndexes();
        if (indexes.isEmpty()) {
            selectedId = -1;
            return;
        }

        const int row = indexes.at(0).row();
        selectedId = model->data(model->index(row, 0)).toInt();

        const auto& e = srv.cauta(selectedId);
        idTxt->setText(QString::number(e.getId()));
        numeTxt->setText(QString::fromStdString(e.getNume()));
        tipTxt->setText(QString::fromStdString(e.getTip()));
        pretTxt->setText(QString::number(e.getPret()));
        });

    QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
        try {
            if (selectedId == -1) {
                throw ValidatorException{ "Niciun rand selectat!" };
            }
            bool okPret = false;
            double pret = pretTxt->text().toDouble(&okPret);
            if (!okPret) {
                throw ValidatorException{ "Pret invalid!" };
            }
            srv.modifica(selectedId, numeTxt->text().toStdString(), tipTxt->text().toStdString(), pret);
            reloadData();
        }
        catch (const exception& ex) {
            QMessageBox::warning(this, "Eroare", ex.what());
        }
        });
}
