#pragma once
#include <QAbstractTableModel>

#include "Melodie.h"
#include <vector>
using std::vector;

class MelodieTableModel : public QAbstractTableModel
{
	vector<Melodie> melodii;
public:
	MelodieTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override{
		return melodii.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override{
		return 6;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setMelodii(const vector<Melodie>& list);
};

