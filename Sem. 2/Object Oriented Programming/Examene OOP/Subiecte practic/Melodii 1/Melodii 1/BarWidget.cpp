#include "BarWidget.h"

#include <QPainter>

void BarWidget::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };

	int w = width();
	int h = height();

	vector<int> freq(11, 0);

	for (const auto& m : melodii) {
		freq[m.getRank()]++;
	}

	int maxim = 0;
	for (const auto& f : freq) {
		if (f > maxim) {
			maxim = f;
		}
	}

	if (maxim == 0) {
		return;
	}

	int latimeBara = w / 11;
	for (int i = 0; i < 11; i++) {
		int inaltime = freq[i] * h / maxim;

		int x = i * latimeBara;
		int y = h - inaltime;

		p.drawRect(x, y, latimeBara - 2, inaltime);
	}

}
