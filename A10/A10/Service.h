#pragma once
#include "Repository.h"
#include "Movie.h"
#include "WatchList.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"
#include "UndoAction.h"
#include <stack>

class Service {
private:
	Repository& repo;
	WatchList& watchlist;
	std::stack<std::unique_ptr<UndoAction>> undoStack;
	std::stack<std::unique_ptr<UndoAction>> redoStack;
public:
	Service(Repository& repo, WatchList& watchlist);
	bool addMovieService(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
	bool removeMovieService(const std::string& title);
	bool updateMovieService(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
	void addWL(Movie& m);
	void removeWL(Movie& m);
	std::vector<Movie>& getAllMoviesService();
	std::vector<Movie> getFilteredService(std::string filter);
	std::vector<Movie>& getAllWatchlist();
	Movie findMovie(std::string title);
	void addMovieDirect(const Movie& m) {repo.addMovieRepo(m);};
	void removeMovieDirect(const std::string& title);
	void updateMovieDirect(const Movie& movie);
	void seeWL();
	void undo();
	void redo();
};