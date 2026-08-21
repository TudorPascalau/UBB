#include "ProdusTableModel.h"

#include <QBrush>

QVariant ProdusTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();
    int col = index.column();

    const auto& p = produse.at(row);

    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0:
            return QString::number(p.getId());
        case 1:
            return QString::fromStdString(p.getNume());
        case 2:
            return QString::fromStdString(p.getTip());
        case 3:
            return QString::number(p.getPret());
        case 4:
            return QString::number(nrVocale(p));
        }
    }

    if (role == Qt::BackgroundRole) {
        if (p.getPret() <= pretSelected) {
            return QBrush(Qt::red);
        }
    }

    return QVariant();
}

void ProdusTableModel::setProduse(const vector<Produs>& list)
{
    beginResetModel();
    produse = list;
    endResetModel();
}

void ProdusTableModel::setPret(int nr)
{
    pretSelected = nr;

    int rows = produse.size();
    int cols = 5;
    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(rows - 1, cols - 1);
    emit dataChanged(topLeft, bottomRight);
}

int ProdusTableModel::nrVocale(const Produs& p) const
{
    const string& nume = p.getNume();
    const string& vocale = "aeiouAEIOU";
    int count = 0;

    for (char c : nume) {
        if (vocale.find(c) != string::npos) {
            count++;
        }
    }

    return count;
}
