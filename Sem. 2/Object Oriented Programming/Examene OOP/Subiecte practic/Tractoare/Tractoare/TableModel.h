#pragma once

#include <QAbstractTableModel>
#include "Tractor.h"

#include <vector>
using std::vector;

class TableModel : public QAbstractTableModel
{
	vector<Tractor> tractoare;
	string tipSelectat;
	int idSelectat;

public:
	TableModel(QObject* parent) : QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return tractoare.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void setTractoare(const vector<Tractor>& tractoare);

	void setTipSelectat(const string& tip);

	void setIdSelectat(int id) {
		idSelectat = id;
	}
	int getIdSelectat() const {
		return idSelectat;
	}
};

