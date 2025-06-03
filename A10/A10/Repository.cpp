#include "Repository.h"
#include "Repository.h"


//Constructor
Repository::Repository(const std::string& filePath) :filepath{ filePath } {
    readFromFile();
}

Repository::~Repository() {
    savetoFile();
}

void Repository::readFromFile() {
    std::ifstream in(this->filepath);
    if (!in.is_open()) return;

    Movie m;
    while (in >> m) {
        movies.push_back(m);
    }
    in.close();
}

void Repository::savetoFile() {
    std::ofstream out(filepath);
    for (const auto& m : movies) {
        out << m;
    }
    out.close();
}

//Adds a new movie to the repository
//Params: Movie type entity
//Returns nothing
void Repository::addMovieRepo(const Movie& movie)
{
    movies.push_back(movie);
    savetoFile();
}

//Removes a movie from the repository by title
void Repository::removeMovieRepo(const std::string& title)
{
    for (auto i = movies.begin(); i != movies.end(); i++) {
        if (i->getTitle() == title) {
            movies.erase(i);
            return;
        }
    }
    savetoFile();
}

//Updates an existing movie with the following parameters
void Repository::updateMovieRepo(const std::string& title, const std::string& genre, int year, int likes, const std::string& trailer) {
    for (auto& movie : movies) {
        if (movie.getTitle() == title) {
            movie.setGenre(genre);
            movie.setYear(year);
            movie.setLikes(likes);
            movie.setTrailer(trailer);
            break;
        }
    }
    savetoFile();

}

//Checks if the Movie existst as it is uniquely identified by title
bool Repository::existsMovie(const std::string& title)
{
    return std::any_of(movies.begin(), movies.end(), [&title](const Movie& m) {
        return m.getTitle() == title;
        });
}

//Returns all movies from the repository
std::vector<Movie>& Repository::getAllMovies()
{
    return movies;
}


