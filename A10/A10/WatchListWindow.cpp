#include "WatchListWindow.h"

WatchListWindow::WatchListWindow(Service& service, QWidget* parent)
    : QWidget(parent) {
    model = new WatchListModel(service.getAllWatchlist(), this);
    table = new QTableView(this);
    table->setModel(model);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(table);
    setLayout(layout);

}
