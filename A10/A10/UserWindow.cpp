#include "UserWindow.h"

UserWindow::UserWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service), currentMovieIndex(0) {
    setupUI();
}

void UserWindow::setupUI() {
    setWindowTitle("User Mode");

    genreEdit = new QLineEdit(this);
    seeMoviesButton = new QPushButton("See Movies by Genre", this);
    nextMovieButton = new QPushButton("Next Movie", this);
    addWatchlistButton = new QPushButton("Add Movie to Watchlist", this);
    seeWatchlistButton = new QPushButton("See Watchlist (Open)", this);
    deleteWatchlistButton = new QPushButton("Delete Movie from Watchlist", this);
    listWatchlistButton = new QPushButton("List Watchlist (in Table)", this);

    movieTable = new QTableWidget(this);
    movieTable->setColumnCount(5);
    movieTable->setHorizontalHeaderLabels({ "Title", "Genre", "Year", "Likes", "Trailer" });

    watchlistTable = new QTableWidget(this);
    watchlistTable->setColumnCount(5);
    watchlistTable->setHorizontalHeaderLabels({ "Title", "Genre", "Year", "Likes", "Trailer" });

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Enter Genre:"));
    mainLayout->addWidget(genreEdit);
    mainLayout->addWidget(seeMoviesButton);
    mainLayout->addWidget(movieTable);
    mainLayout->addWidget(nextMovieButton);
    mainLayout->addWidget(addWatchlistButton);
    mainLayout->addWidget(seeWatchlistButton);
    mainLayout->addWidget(deleteWatchlistButton);
    mainLayout->addWidget(listWatchlistButton);
    mainLayout->addWidget(new QLabel("Watchlist:"));
    mainLayout->addWidget(watchlistTable);

    setLayout(mainLayout);

    connect(seeMoviesButton, &QPushButton::clicked, this, &UserWindow::seeMovies);
    connect(nextMovieButton, &QPushButton::clicked, this, &UserWindow::showNextMovie);
    connect(addWatchlistButton, &QPushButton::clicked, this, &UserWindow::addMovieToWatchlist);
    connect(seeWatchlistButton, &QPushButton::clicked, this, &UserWindow::seeWatchlist);
    connect(deleteWatchlistButton, &QPushButton::clicked, this, &UserWindow::deleteFromWatchlist);
    connect(listWatchlistButton, &QPushButton::clicked, this, &UserWindow::listWatchlist);

}

void UserWindow::seeMovies() {
    QString genre = genreEdit->text();
    if (genre.isEmpty()) {
        filteredMovies = service.getAllMoviesService();
    }
    else {
        filteredMovies = service.getFilteredService(genre.toStdString());
    }

    currentMovieIndex = 0;

    if (filteredMovies.empty()) {
        QMessageBox::information(this, "No Movies", "No movies found for the given genre.");
        movieTable->setRowCount(0);
        nextMovieButton->setEnabled(false);
    }
    else {
        showMovieAtIndex(currentMovieIndex);
        nextMovieButton->setEnabled(filteredMovies.size() > 1);
    }
}

void UserWindow::showMovieAtIndex(int index) {
    if (index >= 0 && index < filteredMovies.size()) {
        movieTable->setRowCount(1);
        const Movie& movie = filteredMovies[index];
        movieTable->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        movieTable->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        movieTable->setItem(0, 2, new QTableWidgetItem(QString::number(movie.getYear())));
        movieTable->setItem(0, 3, new QTableWidgetItem(QString::number(movie.getLikes())));
        movieTable->setItem(0, 4, new QTableWidgetItem(QString::fromStdString(movie.getTrailer())));
    }
}

void UserWindow::showNextMovie() {
    if (filteredMovies.empty()) return;

    currentMovieIndex = (currentMovieIndex + 1) % filteredMovies.size();
    showMovieAtIndex(currentMovieIndex);
}

void UserWindow::addMovieToWatchlist() {
    int row = movieTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a movie to add to the watchlist.");
        return;
    }

    QString title = movieTable->item(row, 0)->text();
    auto movies = service.getAllMoviesService();
    auto it = std::find_if(movies.begin(), movies.end(), [&](const Movie& m) {
        return m.getTitle() == title.toStdString();
        });

    if (it != movies.end()) {
        service.addWL(*it);
        QMessageBox::information(this, "Success", "Movie added to watchlist.");
    }
}

void UserWindow::seeWatchlist() {
    try {
        service.seeWL();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString("Could not open watchlist: %1").arg(e.what()));
    }
}

void UserWindow::deleteFromWatchlist() {
    int row = watchlistTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a movie to delete from the watchlist.");
        return;
    }

    QString title = watchlistTable->item(row, 0)->text();
    auto watchlist = service.getAllWatchlist();
    auto it = std::find_if(watchlist.begin(), watchlist.end(), [&](const Movie& m) {
        return m.getTitle() == title.toStdString();
        });

    if (it != watchlist.end()) {
        service.removeWL(*it);
        QMessageBox::information(this, "Deleted", "Movie removed from watchlist.");
        listWatchlist();
    }
}

void UserWindow::listWatchlist() {
    auto watchlist = service.getAllWatchlist();
    populateWatchlistTable(watchlist);
}

void UserWindow::populateWatchlistTable(const std::vector<Movie>& watchlist) {
    watchlistTable->setRowCount(watchlist.size());
    for (int i = 0; i < watchlist.size(); ++i) {
        const Movie& movie = watchlist[i];
        watchlistTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        watchlistTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        watchlistTable->setItem(i, 2, new QTableWidgetItem(QString::number(movie.getYear())));
        watchlistTable->setItem(i, 3, new QTableWidgetItem(QString::number(movie.getLikes())));
        watchlistTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(movie.getTrailer())));
    }
}
