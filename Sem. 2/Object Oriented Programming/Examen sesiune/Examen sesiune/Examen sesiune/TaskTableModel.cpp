#include "TaskTableModel.h"

QVariant TaskTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();
    int col = index.column();
    const auto& t = tasks.at(row);

    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0:
            return QString::number(t.getId());
        case 1:
            return QString::fromStdString(t.getDescriere());
        case 2:
            return QString::number(t.getProgramatori().size());
        case 3:
            return QString::fromStdString(t.getStare());
        }
    }

    return QVariant();
}

QVariant TaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section < 0 && section > 3) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return QString{"Id"};
        case 1:
            return QString{ "Descriere" };
        case 2:
            return QString{ "Numar programatori" };
        case 3:
            return QString{ "Stare" };
        }
    }

    return QVariant();
}