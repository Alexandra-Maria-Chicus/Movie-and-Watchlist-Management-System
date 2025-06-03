#pragma once
#include "WatchList.h"
#include <fstream>

class CSVWatchList : public WatchList {
public:
	CSVWatchList(const std::string& filename);

	void saveToFile() override;
};

