#pragma once

#include "Melodie.h"

#include <vector>
using std::vector;

#include <QAbstractTableModel>

class MelodieTableModel : public QAbstractTableModel
{
	vector<Melodie> melodii;

public:
	MelodieTableModel(QObject* parent) : QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return melodii.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void setMelodii(const vector<Melodie>& list);
};

