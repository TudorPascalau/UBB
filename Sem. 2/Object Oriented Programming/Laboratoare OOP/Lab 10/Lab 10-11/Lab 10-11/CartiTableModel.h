#pragma once

#include <QAbstractTableModel>
#include <vector>
using std::vector;

#include "Carte.h"
#include "Lista.h"

class CartiTableModel : public QAbstractTableModel
{
private:
	vector<Carte> carti;

public:
	explicit CartiTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

	/*
	* Returneaza numarul de coloane
	* @param parent: "nodul parinte"
	* @return: numarul de randuri
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	/*
	* Returneaza numarul de coloane
	* @param parent: "nodul parinte"
	* @return: numarul de coloane
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	/*
	* Ce se afla intr-un nod
	* @param index:
	* @param role:
	* @return:
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	const Carte& getCarte(int row) const;

	void setCarti(const Lista<Carte>& lista);

	void setCarti(const Lista<Carte>& lista, const Lista<int>& pozitii);

	void setCarti(const std::vector<Carte>& lista);

};

