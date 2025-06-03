#include "CSVWatchList.h"

CSVWatchList::CSVWatchList(const std::string& filename) :WatchList(filename)
{
}

void CSVWatchList::saveToFile()
{
	std::ofstream out(filename);
	if (!out.is_open()) return;

	int index = 1;
	for (const auto& m : list) {
		out << index++ << "," << m.getTitle() << "," << m.getGenre() << "," << m.getYear() << "," << m.getLikes() << "," << m.getTrailer() << "\n";
	}

	out.close();
}