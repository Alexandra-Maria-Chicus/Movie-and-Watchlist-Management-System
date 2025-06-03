#include "Validation.h"

void MovieValidation::validate(const Movie& m)
{
	std::string errors;
	if (m.getTitle().empty()) errors += "Title cannot be empty.\n";
	if (m.getGenre().empty()) errors += "Genre cannot be empty.\n";
	if (m.getYear() < 1500 || m.getYear() > 2025) errors += "Year must be valid.\n";
	if (m.getLikes() < 0)errors += "Likes must be positive.\n";
	if (m.getTrailer().empty()) errors += "Trailer cannot be empty.\n";

	if (!errors.empty())
		throw ValidationException(errors);

}
