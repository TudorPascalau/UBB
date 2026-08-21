#include "XOTableModel.h"

QVariant XOTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();
    int col = index.column();

    const auto& j = jocuri.at(row);
    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0:
            return QString::number(j.getId());
        case 1:
            return QString::number(j.getDim());
        case 2:
            return QString::fromStdString(j.getTabla());
        case 3:
            return QString::fromStdString(j.getPlayer());
        case 4:
            return QString::fromStdString(j.getStare());

        }
    }

    return QVariant();
}

void XOTableModel::setJocuri(const vector<XO>& list)
{
    beginResetModel();
    jocuri = list;
    endResetModel();
}
