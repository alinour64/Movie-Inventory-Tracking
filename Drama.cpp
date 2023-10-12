#include "Drama.h"

// Constructor
Drama::Drama(int stock, const string &director, const string &title, int year)
    : Movie(stock, director, title, year) {}

// Get the movie type
string Drama::getMovieType() const { return "D"; }

// Get the media type
string Drama::getMediaType() const { return mediaType; }

// Overloaded equality operator
bool Drama::operator==(const Movie &other) const {
  return getDirector() == other.getDirector() && getTitle() == other.getTitle();
}
void Drama::print(ostream &os) const {
  os << "D, " << getTitle() << ", " << getStock() << ", " << getDirector()
     << ", " << getYear();
}
