#include "AdminWindow.h"

AdminWindow::AdminWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setupUI();
}

void AdminWindow::setupUI() {
    setWindowTitle("Administrator Mode");

    movieTable = new QTableWidget(this);
    movieTable->setColumnCount(5);
    movieTable->setHorizontalHeaderLabels({ "Title", "Genre", "Year", "Likes", "Trailer" });

    titleEdit = new QLineEdit(this);
    genreEdit = new QLineEdit(this);
    yearEdit = new QLineEdit(this);
    likesEdit = new QLineEdit(this);
    trailerEdit = new QLineEdit(this);

    addButton = new QPushButton("Add Movie", this);
    removeButton = new QPushButton("Remove Movie", this);
    updateButton = new QPushButton("Update Movie", this);
    listButton = new QPushButton("List Movies", this);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);

    connect(undoButton, &QPushButton::clicked, this, &AdminWindow::undoAction);
    connect(redoButton, &QPushButton::clicked, this, &AdminWindow::redoAction);

    QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);

    connect(undoShortcut, &QShortcut::activated, this, &AdminWindow::undoAction);
    connect(redoShortcut, &QShortcut::activated, this, &AdminWindow::redoAction);

    connect(addButton, &QPushButton::clicked, this, &AdminWindow::addMovie);
    connect(removeButton, &QPushButton::clicked, this, &AdminWindow::removeMovie);
    connect(updateButton, &QPushButton::clicked, this, &AdminWindow::updateMovie);
    connect(listButton, &QPushButton::clicked, this, &AdminWindow::listMovies);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(movieTable);
    mainLayout->addWidget(new QLabel("Title"));
    mainLayout->addWidget(titleEdit);
    mainLayout->addWidget(new QLabel("Genre"));
    mainLayout->addWidget(genreEdit);
    mainLayout->addWidget(new QLabel("Year"));
    mainLayout->addWidget(yearEdit);
    mainLayout->addWidget(new QLabel("Likes"));
    mainLayout->addWidget(likesEdit);
    mainLayout->addWidget(new QLabel("Trailer"));
    mainLayout->addWidget(trailerEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(listButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    populateTable();
}

void AdminWindow::populateTable() {
    auto& movies = service.getAllMoviesService();
    movieTable->setRowCount(movies.size());

    for (int i = 0; i < movies.size(); ++i) {
        auto movie = movies[i];
        movieTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        movieTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        movieTable->setItem(i, 2, new QTableWidgetItem(QString::number(movie.getYear())));
        movieTable->setItem(i, 3, new QTableWidgetItem(QString::number(movie.getLikes())));
        movieTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(movie.getTrailer())));
    }
}

void AdminWindow::addMovie() {
    QString title = titleEdit->text();
    QString genre = genreEdit->text();
    int year = yearEdit->text().toInt();
    int likes = likesEdit->text().toInt();
    QString trailer = trailerEdit->text();

    try {
        if (service.addMovieService(title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString())) {
            QMessageBox::information(this, "Success", "Movie added successfully!");
            populateTable();
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void AdminWindow::removeMovie() {
    QString title = titleEdit->text();

    try {
        if (service.removeMovieService(title.toStdString())) {
            QMessageBox::information(this, "Success", "Movie removed successfully!");
            populateTable();
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void AdminWindow::updateMovie() {
    QString title = titleEdit->text();
    QString genre = genreEdit->text();
    int year = yearEdit->text().toInt();
    int likes = likesEdit->text().toInt();
    QString trailer = trailerEdit->text();

    try {
        if (service.updateMovieService(title.toStdString(), genre.toStdString(), year, likes, trailer.toStdString())) {
            QMessageBox::information(this, "Success", "Movie updated successfully!");
            populateTable();
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void AdminWindow::listMovies() {
    populateTable();
}

void AdminWindow::undoAction() {
    try {
        service.undo();
        populateTable(); // Refresh the table
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo Failed", e.what());
    }
}

void AdminWindow::redoAction() {
    try {
        service.redo();
        populateTable(); // Refresh the table
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Redo Failed", e.what());
    }
}
