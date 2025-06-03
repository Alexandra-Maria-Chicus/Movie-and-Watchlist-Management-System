#pragma once
#include "Movie.h"
#include <vector>
#include <iostream>
#include <string>

class WatchList {
protected:
	std::vector<Movie> list;
	std::string filename;
public:
	WatchList(const std::string& filename) : filename(filename) {}
	virtual ~WatchList();
	void addToWatchList(const Movie& M);
	void removeFromWatchList(const Movie& M);
	std::vector<Movie>& getWatchList();

	virtual void saveToFile() = 0;
	void openFile() const { system(("start \"\" \"" + filename + "\"").c_str()); };
};