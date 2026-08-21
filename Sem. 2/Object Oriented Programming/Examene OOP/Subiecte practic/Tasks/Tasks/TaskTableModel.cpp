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
