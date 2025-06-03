#include "Movie.h"
#include <iostream>
#include <sstream>

//Constructor
Movie::Movie() : title{ "" }, genre{ "" }, year{ 0 }, likes{ 0 }, trailer{ "" }
{
}

Movie::Movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) :
	title{ title }, genre{ genre }, year{ year }, likes{ likes }, trailer{ trailer }
{
}

Movie::~Movie()
{
}

Movie::Movie(const Movie& m)
{
	this->title = m.title;
	this->genre = m.genre;
	this->year = m.year;
	this->likes = m.likes;
	this->trailer = m.trailer;
}

void Movie::setTitle(const std::string& title)
{
	if (title.empty())
		return;
	this->title = title;
}

void Movie::setGenre(const std::string& genre)
{
	if (genre.empty())
		return;
	this->genre = genre;
}

void Movie::setYear(int year)
{
	if (year < 1880 || year>2025)
		return;
	this->year = year;
}

void Movie::setLikes(int likes)
{
	if (likes < 0)
		return;
	this->likes = likes;
}

void Movie::setTrailer(const std::string& trailer)
{
	if (strlen(trailer.c_str()) == 0)
		return;
	this->trailer = trailer;
}


std::ostream& operator<<(std::ostream& out, const Movie& movie) {
	out << movie.title << "," << movie.genre << "," << movie.year << "," << movie.likes << "," << movie.trailer << "\n";
	return out;
}

std::istream& operator>>(std::istream& in, Movie& movie) {
	std::string line;
	if (std::getline(in, line)) {
		std::stringstream ss(line);
		std::string title, genre, trailer;
		int year, likes;

		std::getline(ss, title, ',');
		std::getline(ss, genre, ',');
		ss >> year;
		ss.ignore();
		ss >> likes;
		ss.ignore();
		std::getline(ss, trailer);

		movie = Movie(title, genre, year, likes, trailer);
	}
	return in;
}
