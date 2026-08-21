#pragma once

#include <QtWidgets/QWidget>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QPainter>
#include <QMouseEvent>

#include "Service.h"
#include "TableModel.h"

class WheelsWidget;

class GUI : public QWidget
{
    Q_OBJECT

    Service& service;
	QTableView* tableView;
	TableModel* tableModel;
	WheelsWidget* wheelsWidget;

	QLineEdit* idEdit;
	QLineEdit* denumireEdit;
	QLineEdit* tipEdit;
	QLineEdit* nrRotiEdit;
	QPushButton* btnAdd;
	QFormLayout* addFormLayout;

	QComboBox* comboTip;

	QHBoxLayout* topLayout;
	QVBoxLayout* sideLayout;
	QVBoxLayout* fullLayout;

	void initGUI();
	void connectSignals();
	void reloadData();

	int lastSelectedId = -1;
	void reloadCombo();

	void readForm(int& id, string& descriere, string& tip, int& nrRoti) const;

	void createTableView();
	void createAddForm();

	void createSideLayout();
	void createTopLayout();
	void createFullLayout();

	void connectAddButton();
	void connnectCombo();
	void connectTableSelect();
	void connectWheelClick();

public:
	GUI(Service& service, QWidget* parent = nullptr);
};

class WheelsWidget : public QWidget
{
	Q_OBJECT

	int nrRoti = 0;

public:
	WheelsWidget(QWidget* parent = nullptr) : QWidget(parent) {}
	void setNrRoti(int nr) {
		nrRoti = nr;
		update();
	}

signals:
	void wheelClicked();

protected:
	void paintEvent(QPaintEvent*) override;

	void mousePressEvent(QMouseEvent* ev) override;
};

