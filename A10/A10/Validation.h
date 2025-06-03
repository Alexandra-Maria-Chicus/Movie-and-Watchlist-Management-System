#pragma once
#include "Movie.h"
#include "Exception.h"

class MovieValidation {
public:
	static void validate(const Movie& m);
};

