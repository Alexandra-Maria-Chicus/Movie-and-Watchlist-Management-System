#include "WatchList.h"



WatchList::~WatchList()
{
}

void WatchList::addToWatchList(const Movie& M)
{
	list.push_back(M);
	saveToFile();
}


//removes the movie from the watchlist
//Parametars: Movie M
//Returns nothing
void WatchList::removeFromWatchList(const Movie& M)
{
	for (auto it = list.begin(); it != list.end(); it++) {
		if (it->getTitle() == M.getTitle()) {
			list.erase(it);
			return;
		}
	}
	saveToFile();
}

//Returns a DynamicVector of all the watchlist movies
std::vector<Movie>& WatchList::getWatchList()
{
	return this->list;
}
