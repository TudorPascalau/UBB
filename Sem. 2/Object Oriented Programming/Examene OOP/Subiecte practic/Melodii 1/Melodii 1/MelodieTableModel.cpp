#include "MelodieTableModel.h"

#include <algorithm>

QVariant MelodieTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    

    int row = index.row();
    int col = index.column();

    const Melodie& m = melodii.at(row);

    int count = count_if(melodii.begin(), melodii.end(), [&](const Melodie& mel) {
        return mel.getRank() == m.getRank();
    });

    if (role == Qt::DisplayRole) {
        switch (col) {
            case 0:
                return QString::number(m.getId());
            case 1:
                return QString::fromStdString(m.getTitlu());
            case 2:
                return QString::fromStdString(m.getArtist());
            case 3:
                return QString::number(m.getRank());
            case 4:
                return QString::number(count);
        }
    }

    return QVariant();
}

QVariant MelodieTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Id");
        case 1:
            return QString("Titlu");
        case 2:
            return QString("Artist");
        case 3:
            return QString("Rank");
        case 4:
            return QString("Melodii cu acelasi rank");
        }
    }

    return QVariant();
}

void MelodieTableModel::setMelodii(const vector<Melodie>& list)
{
    beginResetModel();
    melodii = list;
    endResetModel();
}
