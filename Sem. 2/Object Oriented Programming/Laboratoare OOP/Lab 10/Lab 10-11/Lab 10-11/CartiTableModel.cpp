#include "CartiTableModel.h"

int CartiTableModel::rowCount(const QModelIndex& parent) const {
	if (parent.isValid()) {
		return 0;
	}
	return static_cast<int>(carti.size());
}

int CartiTableModel::columnCount(const QModelIndex& parent) const {
	if (parent.isValid()) {
		return 0;
	}
	return 5;
}

QVariant CartiTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant{};
    }

    const Carte& c = carti.at(index.row());

    switch (index.column()) {
        case 0: return c.getId();
        case 1: return QString::fromStdString(c.getTitlu());
        case 2: return QString::fromStdString(c.getAutor());
        case 3: return c.getAn();
        case 4: return QString::fromStdString(c.getGen());
        default: return QVariant{};
    }
}

QVariant CartiTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant{};
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Id";
        case 1: return "Titlu";
        case 2: return "Autor";
        case 3: return "An";
        case 4: return "Gen";
        default: return QVariant{};
        }
    }

    return section + 1;
}

const Carte& CartiTableModel::getCarte(int row) const {
    return carti.at(row);
}

void CartiTableModel::setCarti(const Lista<Carte>& lista) {
    beginResetModel();
    carti.clear();

    for (const auto& carte : lista) {
        carti.push_back(carte);
    }

    endResetModel();
}

void CartiTableModel::setCarti(const Lista<Carte>& lista, const Lista<int>& pozitii) {
    beginResetModel();  
    carti.clear();

    for (const int poz : pozitii) {
        carti.push_back(lista.get(poz));
    }

    endResetModel();
}

void CartiTableModel::setCarti(const std::vector<Carte>& lista) {
    beginResetModel();
    carti = lista;
    endResetModel();
}