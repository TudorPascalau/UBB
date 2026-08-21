#pragma once

#include <QWidget>
#include <QLabel>
#include <string>
using std::string;

class ProductWindow : public QWidget
{
	string tip;
	QLabel* nrLabel;

public:
	ProductWindow(int count, string tip, QWidget* parent = nullptr);
	void setCount(int count);
};

