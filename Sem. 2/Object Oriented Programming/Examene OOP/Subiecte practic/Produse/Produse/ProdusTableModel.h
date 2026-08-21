#pragma once
#include "Produs.h"

#include <QAbstractTableModel>
#include <vector>
using std::vector;

class ProdusTableModel : public QAbstractTableModel
{
	vector<Produs> produse;
	int pretSelected = -1;
	int nrVocale(const Produs& p) const;

public:
	ProdusTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setProduse(const vector<Produs>& list);

	void setPret(int nr);
};

