#pragma once
#include "Melodie.h"

#include <QWidget>
#include <vector>
using std::vector;
#include <QPaintEvent>

class CircleWidget : public QWidget
{
	int nrMelodii = 0;

public:
	CircleWidget(QWidget* parent) : QWidget(parent) {
		this->setFixedSize(80, 80);
	}
	void setNrMelodii(int nr) {
		nrMelodii = nr;
		update();
	}
protected:
	void paintEvent(QPaintEvent* ev) override;
};

