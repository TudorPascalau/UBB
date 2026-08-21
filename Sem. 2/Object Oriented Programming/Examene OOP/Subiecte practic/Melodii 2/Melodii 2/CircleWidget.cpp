#include "CircleWidget.h"

#include <QPainter>

void CircleWidget::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };

    int cx = width() / 2;
    int cy = height() / 2;

    int razaStart = 8;
    int pas = 7;

    for (int i = 0; i < nrMelodii; i++) {
        int r = razaStart + i * pas;
        p.drawEllipse(QPoint(cx,cy), r, r);
    }
}
