#include "GUI.h"
#include "AdminWindow.h"
#include "UserWindow.h"

GUI::GUI(Service& service, QWidget* parent) : QWidget(parent), service(service) {
    setupUI();
}

void GUI::setupUI() {
    setWindowTitle("Movie Management");
    //setFixedSize(800, 600);

    stackedWidget = new QStackedWidget(this); //holds multiple widgets (pages) but shows only one at a time.
    adminWindow = new AdminWindow(service);
    userWindow = new UserWindow(service);
    watchlistWindow = new WatchListWindow(service, this);

    stackedWidget->addWidget(adminWindow);
    stackedWidget->addWidget(userWindow);
    stackedWidget->addWidget(watchlistWindow);

    adminButton = new QPushButton("Admin Mode", this);
    userButton = new QPushButton("User Mode", this);
    watchlistButton = new QPushButton("Watchlist Mode", this);
    connect(watchlistButton, &QPushButton::clicked, this, &GUI::switchToWatchlistMode);
    connect(adminButton, &QPushButton::clicked, this, &GUI::switchToAdminMode);
    connect(userButton, &QPushButton::clicked, this, &GUI::switchToUserMode);

    QHBoxLayout* buttonLayout = new QHBoxLayout(); //arranges widgets horizontally.
    buttonLayout->addWidget(adminButton);
    buttonLayout->addWidget(userButton);
    buttonLayout->addWidget(watchlistButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}

void GUI::switchToAdminMode() {
    stackedWidget->setCurrentWidget(adminWindow);
}

void GUI::switchToUserMode() {
    stackedWidget->setCurrentWidget(userWindow);
}

void GUI::switchToWatchlistMode() {
    watchlistWindow->refresh();
    stackedWidget->setCurrentWidget(watchlistWindow);
}
