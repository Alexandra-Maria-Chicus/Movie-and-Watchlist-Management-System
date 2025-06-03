#include "Service.h"
#include "Validation.h"
#include "Exception.h"


//Service constructor
Service::Service(Repository& repo, WatchList& watchlist) :repo(repo), watchlist{ watchlist }
{
}

//Checks if the movie exists and then calls the function that adds it to the repository
//Returns True if it was added successfully
//Returns False if the Movie title already exists
bool Service::addMovieService(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer)
{
	Movie m(title, genre, year, likes, trailer);
	MovieValidation::validate(m);
	if (repo.existsMovie(title))
		throw RepositoryException("Movie already exists!");
	repo.addMovieRepo(m);
	undoStack.push(std::make_unique<UndoAdd>(*this, m));
	redoStack = {};
	return true;
}

//Checks if the movie exists and then calls the function that removess it from the repository
//Returns True if it was removed successfully
//Returns False if the Movie title doesn't exists
bool Service::removeMovieService(const std::string& title)
{
	if (!repo.existsMovie(title))
		throw RepositoryException("Movie does not exist.");
	Movie m = findMovie(title);  
	repo.removeMovieRepo(title);

	undoStack.push(std::make_unique<UndoRemove>(*this, m));
	redoStack = {};
	return true;
}

//Checks if the movie exists and then calls the function that updates it 
//Returns True if it was updated successfully
//Returns False if the Movie title doesn't exists
bool Service::updateMovieService(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer)
{
	if (!repo.existsMovie(title))
		throw RepositoryException("Movie does not exist!");

	Movie oldMovie = findMovie(title); 
	Movie newMovie(title, genre, year, likes, trailer);
	MovieValidation::validate(newMovie);

	repo.updateMovieRepo(title, genre, year, likes, trailer);

	undoStack.push(std::make_unique<UndoUpdate>(*this, oldMovie, newMovie));
	redoStack = {};
	return true;
}

void Service::addWL(Movie& m)
{
	this->watchlist.addToWatchList(m);
}

void Service::removeWL(Movie& m)
{
	this->watchlist.removeFromWatchList(m);
}


std::vector<Movie>& Service::getAllMoviesService()
{
	return repo.getAllMovies();
}

std::vector<Movie> Service::getFilteredService(std::string filter)
{
	std::vector<Movie> movies = repo.getAllMovies();
	std::vector<Movie> temp;
	for (int i = 0; i < movies.size(); i++)
		if (movies[i].getGenre() == filter)
			temp.push_back(movies[i]);
	return temp;
}

std::vector<Movie>& Service::getAllWatchlist()
{
	return watchlist.getWatchList();
}

Movie Service::findMovie(std::string title)
{
	std::vector<Movie> movies = repo.getAllMovies();
	for (auto m : movies)
		if (m.getTitle() == title)
			return m;
}

void Service::seeWL()
{
	watchlist.openFile();
}

void Service::removeMovieDirect(const std::string& title) {
	repo.removeMovieRepo(title);  
}

void Service::updateMovieDirect(const Movie& movie) {
	repo.updateMovieRepo(
		movie.getTitle(),
		movie.getGenre(),
		movie.getYear(),
		movie.getLikes(),
		movie.getTrailer()
	);
}

void Service::undo() {
	if (undoStack.empty()) throw std::runtime_error("No operations to undo.");
	auto action = std::move(undoStack.top());
	undoStack.pop();
	action->undo();
	redoStack.push(std::move(action));
}

void Service::redo() {
	if (redoStack.empty()) throw std::runtime_error("No operations to redo.");
	auto action = std::move(redoStack.top());
	redoStack.pop();
	action->redo();
	undoStack.push(std::move(action));
}