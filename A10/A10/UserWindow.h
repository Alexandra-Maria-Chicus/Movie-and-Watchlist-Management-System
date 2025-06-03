#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <vector>
#include "Service.h"
#include "Movie.h"

class UserWindow : public QWidget {
    Q_OBJECT

public:
    UserWindow(Service& service, QWidget* parent = nullptr);

private:
    Service& service;

    QLineEdit* genreEdit;
    QPushButton* seeMoviesButton;
    QPushButton* nextMovieButton;
    QPushButton* addWatchlistButton;
    QPushButton* seeWatchlistButton;
    QPushButton* deleteWatchlistButton;
    QPushButton* listWatchlistButton;

    QTableWidget* movieTable;
    QTableWidget* watchlistTable;

    std::vector<Movie> filteredMovies;
    int currentMovieIndex;

    void setupUI();
    void showMovieAtIndex(int index);
    void populateWatchlistTable(const std::vector<Movie>& watchlist);

private slots:
    void seeMovies();
    void showNextMovie();
    void addMovieToWatchlist();
    void seeWatchlist();
    void deleteFromWatchlist();
    void listWatchlist();
};
