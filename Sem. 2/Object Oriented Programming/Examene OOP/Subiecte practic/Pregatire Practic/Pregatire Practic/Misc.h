// === BarWidget.h ===
#pragma once
#include "Produs.h"

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <vector>
using std::vector;

class BarWidget : public QWidget {
    Q_OBJECT
        vector<Produs> elems;

public:
    explicit BarWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumHeight(120); // ca widgetul desenat sa aiba spatiu vizibil
    }

    void setElems(const vector<Produs>& list) {
        elems = list;
        update(); // cere Qt-ului sa apeleze paintEvent cand poate
    }

protected:
    void paintEvent(QPaintEvent* ev) override;
};

// === BarWidget.cpp ===
#include "BarWidget.h"

void BarWidget::paintEvent(QPaintEvent* ev) {
    Q_UNUSED(ev);
    QPainter p{ this }; // QPainter se foloseste in paintEvent

    const int w = width();
    const int h = height();
    if (elems.empty()) {
        p.drawText(rect(), Qt::AlignCenter, "Nu exista date");
        return;
    }

    const int barW = std::max(1, w / static_cast<int>(elems.size()));
    int maxVal = 1;
    for (const auto& e : elems) {
        maxVal = std::max(maxVal, e.getValoare()); // adapteaza getterul
    }

    for (int i = 0; i < static_cast<int>(elems.size()); ++i) {
        const int barH = elems.at(i).getValoare() * h / maxVal;
        const int x = i * barW;
        const int y = h - barH;
        p.drawRect(x, y, barW - 2, barH);
    }
}
