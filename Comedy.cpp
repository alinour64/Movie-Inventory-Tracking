#include "Comedy.h"

// Constructor
Comedy::Comedy(int stock, const string &director, const string &title, int year)
    : Movie(stock, director, title, year) {}

// Get the movie type
string Comedy::getMovieType() const { return "F"; }

// Get the media type
string Comedy::getMediaType() const { return mediaType; }

// Equality operator overload
bool Comedy::operator==(const Movie &other) const {
  if (getTitle() == other.getTitle()) {
    return getYear() == other.getYear();
  }

  return false;
}
void Comedy::print(ostream &os) const {
  os << "F, " << getTitle() << ", " << getStock() << ", " << getDirector()
     << ", " << getYear();
}
