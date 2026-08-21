#include "ProductWindow.h"

#include <QVBoxLayout>

ProductWindow::ProductWindow(int count, string tip, QWidget* parent) 
	: QWidget(parent), tip{tip}
{
	resize(300, 50);
	setWindowTitle(QString::fromStdString(tip));

	nrLabel = new QLabel{ QString::number(count), this};
	auto* ly = new QVBoxLayout;
	ly->addWidget(nrLabel);
	setLayout(ly);
}

void ProductWindow::setCount(int count)
{
	nrLabel->setText(QString::number(count));
}
