// === ProdusTableModel.h ===
#pragma once
#include "Produs.h"

#include <QAbstractTableModel>
#include <QBrush>
#include <QString>
#include <vector>
using std::vector;

class ProdusTableModel : public QAbstractTableModel {
    vector<Produs> elems;

public:
    explicit ProdusTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return static_cast<int>(elems.size());
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 4; // modifica numarul de coloane dupa domain
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setElems(const vector<Produs>& list) {
        beginResetModel();     // anunta QTableView ca datele se refac complet
        elems = list;
        endResetModel();       // QTableView se redeseneaza automat
    }
};

// === ProdusTableModel.cpp ===
#include "ProdusTableModel.h"

QVariant ProdusTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant{};
    }

    const int row = index.row();
    const int col = index.column();
    const auto& e = elems.at(row);

    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0: return QString::number(e.getId());
        case 1: return QString::fromStdString(e.getNume());
        case 2: return QString::fromStdString(e.getTip());
        case 3: return QString::number(e.getPret());
        default: return QVariant{};
        }
    }

    // Exemplu optional: coloreaza randurile dupa o conditie.
    // if (role == Qt::BackgroundRole && e.getPret() > 100) return QBrush{ Qt::yellow };

    return QVariant{};
}

QVariant ProdusTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0: return "Id";
        case 1: return "Nume";
        case 2: return "Tip";
        case 3: return "Pret";
        default: return QVariant{};
        }
    }
    return QVariant{};
}
