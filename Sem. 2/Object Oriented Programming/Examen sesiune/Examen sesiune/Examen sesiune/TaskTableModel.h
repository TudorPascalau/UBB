#pragma once
#include "Task.h"
#include <QAbstractTableModel>

class TaskTableModel : public QAbstractTableModel
{
	vector<Task> tasks;
public:

	/*
	* Constructor table model custom
	*/
	TaskTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

	/*
	* Metoda ce returneaza numarul de randuri al tabelului
	* @return: numar randuri table
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const {
		return tasks.size();
	}

	/*
	* Metoda ce returneaza numarul de coloane al tabelului
	* @return: numar coloane (4)
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const {
		return 4;
	}

	/*
	* Metoda ce stabileste modul in care sunt afisate elementele in table
	* @param index: celula in care se afiseaza
	* @param role: atributul de afisat
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	/*
	* Metoda ce stabileste modul in care sunt afisate elementele capetele de table
	* @param section: coloana
	* @param oritentation: orientarea 
	* @param role: atributul de afisat
	*/
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	/*
	* Metoda ce seteaza task-urile modelului
	* @param list: lista de task-uri ce va fi setata
	* Post: este restetat modelul cu noua lista
	*/
	void setTasks(const vector<Task>& list) {
		beginResetModel();
		tasks = list;
		endResetModel();
	}

	/*
	* Metoda ce gaseste Task-ul reprezentat pe un anumit rand
	* @param sourceRow: randul Task-ului in model
	* @return Task-ul de pe rand
	*/
	Task getTask(int sourceRow) const {
		return tasks.at(sourceRow);
	}
};

