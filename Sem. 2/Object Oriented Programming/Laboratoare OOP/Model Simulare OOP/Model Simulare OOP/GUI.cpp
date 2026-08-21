#include "GUI.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

GUI::GUI(Service& srv) : service{ srv }
{
    initGUI();
    loadData(srv.getAllNesortat());
    connectSignals();
}

void GUI::initGUI() {
	auto* mainLayout = new QVBoxLayout;
	setLayout(mainLayout);

	list = new QListWidget;
	mainLayout->addWidget(list);

	auto* btnLayout = new QHBoxLayout;
	btnInchiriaza = new QPushButton("Inchiriaza");
	btnSortMarime = new QPushButton("Sorteaza marime");
	btnSortPret = new QPushButton("Sorteaza pret");
	btnNesortat = new QPushButton("Nesortat");

	btnLayout->addWidget(btnInchiriaza);
	btnLayout->addWidget(btnSortMarime);
	btnLayout->addWidget(btnSortPret);
	btnLayout->addWidget(btnNesortat);

	mainLayout->addLayout(btnLayout);

	resize(700, 400);

}

void GUI::connectSignals() {
	QObject::connect(btnInchiriaza, &QPushButton::clicked, [&]() {
		auto selected = list->selectedItems();

		if (selected.isEmpty()) {
			QMessageBox::warning(this, "Eroare", "Nicio selectie.");
			return;
		}

		int cod = selected.at(0)->data(Qt::UserRole).toInt();
		try {
			service.inchireaza(cod);
			loadData(service.getAllNesortat());
		}
		catch (RepoError& re) {
			QString msg = QString::fromStdString(re.getMessage());
			QMessageBox::warning(this, "Eroare", msg);
		}
	});

	QObject::connect(btnNesortat, &QPushButton::clicked, [&]() {
		loadData(service.getAllNesortat());
	});

	QObject::connect(btnSortMarime, &QPushButton::clicked, [&]() {
		loadData(service.sortMarime());
	});

	QObject::connect(btnSortPret, &QPushButton::clicked, [&]() {
		loadData(service.sortPret());
	});
}

void GUI::loadData(const vector<Rochie>& rochii) {
	list->clear();
	for (const auto& r : rochii) {
		QString text = QString::fromStdString(r.getDenumire() + " | " + r.getMarime() + " | " + std::to_string(r.getPret()));
		auto* item = new QListWidgetItem(text);

		item->setData(Qt::UserRole, r.getCod());
		if (r.getDisponibil() == true) {
			item->setBackground(Qt::green);
		}
		else {
			item->setBackground(Qt::red);
		}

		item->setForeground(Qt::black);

		list->addItem(item);
	}
}

