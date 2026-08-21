#include "TableModel.h"

#include <QBrush>
#include <QDebug>

QVariant TableModel::data(const QModelIndex& index, int role) const {

	if (!index.isValid())
		return QVariant();

	const Tractor& t = tractoare.at(index.row());

	if (role == Qt::DisplayRole) {

		switch (index.column()) {
		case 0:
			return t.getId();
		case 1:
			return QString::fromStdString(t.getDenumire());
		case 2:
			return QString::fromStdString(t.getTip());
		case 3:
			return t.getNrRoti();
		case 4:
			return count_if(tractoare.begin(), tractoare.end(),
				[&](const Tractor& other) {
					return other.getTip() == t.getTip();
				});
		default:
			return QVariant();
		}
	}

	if (role == Qt::BackgroundRole) {
		if (t.getTip() == tipSelectat) {
			return QBrush(Qt::red);
		}
	}

	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return "ID";
		case 1:
			return "Denumire";
		case 2:
			return "Tip";
		case 3:
			return "Nr roti";
		case 4:
			return "Nr tractoare cu acelasi tip";
		default:
			return QVariant();
		}
	}
	return QVariant();
}

void TableModel::setTractoare(const vector<Tractor>& lista) {
	beginResetModel();
	tractoare = lista;
	endResetModel();
}

void TableModel::setTipSelectat(const string& tip)
{
	tipSelectat = tip;
	emit dataChanged(
		index(0, 0),
		index(rowCount() - 1, columnCount() - 1)
	);

}

