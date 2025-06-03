#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include "Service.h"
#include "AdminWindow.h"
#include "UserWindow.h"
#include "WatchListWindow.h"

class GUI : public QWidget {
    Q_OBJECT

public:
    GUI(Service& service, QWidget* parent = nullptr);

private:
    Service& service;
    QStackedWidget* stackedWidget;
    AdminWindow* adminWindow;
    UserWindow* userWindow;
    QPushButton* watchlistButton;
    WatchListWindow* watchlistWindow;
    QPushButton* adminButton;
    QPushButton* userButton;
    QVBoxLayout* mainLayout;

    void setupUI();

private slots:
    void switchToAdminMode();
    void switchToUserMode();
    void switchToWatchlistMode();
};
