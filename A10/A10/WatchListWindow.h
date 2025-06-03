#pragma once

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include "Service.h"
#include "WatchListModel.h"

class WatchListWindow : public QWidget {
    Q_OBJECT

private:
    WatchListModel* model;
    QTableView* table;

public:
    explicit WatchListWindow(Service& service, QWidget* parent = nullptr);
    void refresh() { model->layoutChanged(); };
};
