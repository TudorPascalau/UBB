#pragma once
#include "Melodie.h"

#include <QtWidgets/QWidget>
#include <QPaintEvent>
#include <vector>
using std::vector;

class BarWidget : public QWidget
{
	Q_OBJECT

	vector<Melodie> melodii;

public:
	BarWidget(QWidget* parent = nullptr) : QWidget{parent} {}
	void setMelodii(const vector<Melodie>& mel) {

		melodii = mel;
		update();
	}
	
protected:
	void paintEvent(QPaintEvent* ev) override;
};

