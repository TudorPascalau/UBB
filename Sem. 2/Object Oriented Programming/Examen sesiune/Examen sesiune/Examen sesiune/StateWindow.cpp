#include "StateWindow.h"

StateWindow::StateWindow(Service& srv, TaskTableModel* sourceModel, const string& stare, QWidget* parent)
    : QWidget{ parent }, srv{ srv }, sourceModel{ sourceModel }, stare{ stare } {

    proxyModel = new QSortFilterProxyModel{ this };
    proxyModel->setSourceModel(sourceModel);
    proxyModel->setFilterKeyColumn(3);
    proxyModel->setFilterFixedString(QString::fromStdString(stare));

    initGUI();
    connectSignals();

    setWindowTitle(QString::fromStdString(stare));
    resize(400, 200);
}

void StateWindow::initGUI() {
    auto* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    table->setModel(proxyModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    mainLayout->addWidget(table);

    auto* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(btnOpen);
    btnLayout->addWidget(btnInprogress);
    btnLayout->addWidget(btnClose);

    mainLayout->addLayout(btnLayout);
}

void StateWindow::connectSignals() {
    QObject::connect(btnOpen, &QPushButton::clicked, [&]() {
        changeSelectedTaskState("open");
        });

    QObject::connect(btnInprogress, &QPushButton::clicked, [&]() {
        changeSelectedTaskState("inprogress");
        });

    QObject::connect(btnClose, &QPushButton::clicked, [&]() {
        changeSelectedTaskState("closed");
        });
}

void StateWindow::changeSelectedTaskState(const std::string& newState) {
    QModelIndex proxyIndex = table->currentIndex();

    if (!proxyIndex.isValid()) {
        QMessageBox::warning(this, "Warning", "Nu este selectat niciun task.");
        return;
    }

    QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);

    int sourceRow = sourceIndex.row();
    int id = sourceModel->getTask(sourceRow).getId();

    srv.modifica(id, newState);

    sourceModel->setTasks(srv.getSortatStare());
}