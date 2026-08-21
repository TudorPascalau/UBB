#pragma once
#include "XO.h"
#include <QAbstractTableModel>

#include <vector>
using std::vector;

class XOTableModel : public QAbstractTableModel
{
	vector<XO> jocuri;
public:
	XOTableModel(QObject* parent) : QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return jocuri.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setJocuri(const vector<XO>& list);
};

