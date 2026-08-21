#pragma once
#include "Task.h"
#include <QAbstractTableModel>

class TaskTableModel : public QAbstractTableModel
{
	vector<Task> tasks;
public:
	TaskTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return tasks.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	void setTasks(const vector<Task>& list) {
		beginResetModel();
		tasks = list;
		endResetModel();
	}

	Task getTask(int sourceRow) const {
		return tasks.at(sourceRow);
	}
};

