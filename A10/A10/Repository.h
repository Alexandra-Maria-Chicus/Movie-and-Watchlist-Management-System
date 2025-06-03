#pragma once
#include <vector>
#include <algorithm>
#include "Movie.h"
#include <iostream>
#include <string>
#include <fstream>

class Repository
{
private:
	std::vector<Movie> movies;
	std::string filepath;

	void readFromFile();
	void savetoFile();

public:
	Repository(const std::string& filePath);
	~Repository();
	void addMovieRepo(const Movie& movie);
	void removeMovieRepo(const std::string& title);
	void updateMovieRepo(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
	bool existsMovie(const std::string& title);
	std::vector<Movie>& getAllMovies();
};