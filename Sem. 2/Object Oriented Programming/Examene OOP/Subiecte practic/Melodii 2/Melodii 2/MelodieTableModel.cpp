#include "MelodieTableModel.h"


QVariant MelodieTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();
    int col = index.column();

    const auto& m = melodii.at(row);
    string artist = m.getArtist();
    string gen = m.getGen();

    int countArtist = count_if(melodii.begin(), melodii.end(), [&](const Melodie& mel) {
        return mel.getArtist() == artist;
        });

    int countGen = count_if(melodii.begin(), melodii.end(), [&](const Melodie& mel) {
        return mel.getGen() == gen;
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
            return QString::fromStdString(m.getGen());
        case 4:
            return QString::number(countArtist);
        case 5:
            return QString::number(countGen);
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
