#include "HTMLWatchList.h"
#include <iostream>

HTMLWatchList::HTMLWatchList(const std::string& filename) : WatchList(filename) {}

void HTMLWatchList::saveToFile() {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cout << "Unable to open file for writing!" << std::endl;
        return;
    }

    out << "<!DOCTYPE html>\n<html>\n<head>\n<title>Watchlist</title>\n</head>\n<body>\n";
    out << "<table border=\"1\">\n";
    out << "    <tr>\n";
    out << "        <td>Title</td>\n";
    out << "        <td>Genre</td>\n";
    out << "        <td>Year</td>\n";
    out << "        <td>Likes</td>\n";
    out << "        <td>Trailer</td>\n";
    out << "    </tr>\n";

    for (const auto& movie : list) {
        out << "    <tr>\n";
        out << "        <td>" << movie.getTitle() << "</td>\n";
        out << "        <td>" << movie.getGenre() << "</td>\n";
        out << "        <td>" << movie.getYear() << "</td>\n";
        out << "        <td>" << movie.getLikes() << "</td>\n";
        out << "        <td><a href=\"" << movie.getTrailer() << "\">Link</a></td>\n";
        out << "    </tr>\n";
    }

    out << "</table>\n</body>\n</html>\n";

    out.close();
}
