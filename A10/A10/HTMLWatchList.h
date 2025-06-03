#pragma once
#include "WatchList.h"
#include <fstream>

class HTMLWatchList : public WatchList {
public:
	HTMLWatchList(const std::string& filename);

	void saveToFile() override;
};

