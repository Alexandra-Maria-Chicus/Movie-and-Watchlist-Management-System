#pragma once
#include <iostream>
#include <string>

class Movie
{
private:
	std::string title;
	std::string genre;
	int year;
	int likes;
	std::string trailer;

public:
	Movie();
	Movie(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer);
	~Movie();
	Movie(const Movie& m);
	std::string getTitle() const { return this->title; }
	void setTitle(const std::string& title);
	std::string getGenre() const { return this->genre; }
	void setGenre(const std::string& genre);
	int getYear() const { return this->year; }
	void setYear(int year);
	int getLikes() const { return this->likes; }
	void setLikes(int likes);
	std::string getTrailer() const { return this->trailer; }
	void setTrailer(const std::string& trailer);

	friend std::ostream& operator<<(std::ostream& out, const Movie& movie);
	friend std::istream& operator>>(std::istream& in, Movie& movie);
};