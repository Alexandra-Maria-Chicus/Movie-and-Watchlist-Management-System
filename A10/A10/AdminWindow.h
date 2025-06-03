#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QShortCut>
#include "Service.h"


class AdminWindow : public QWidget {
    Q_OBJECT

public:
    AdminWindow(Service& service, QWidget* parent = nullptr);

private:
    Service& service;
    QTableWidget* movieTable;
    QLineEdit* titleEdit;
    QLineEdit* genreEdit;
    QLineEdit* yearEdit;
    QLineEdit* likesEdit;
    QLineEdit* trailerEdit;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* listButton;
    QPushButton* undoButton;
    QPushButton* redoButton;

    void setupUI();
    void populateTable();
    void addMovie();
    void removeMovie();
    void updateMovie();
    void listMovies();
    void undoAction();
    void redoAction();
};
