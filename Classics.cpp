#include "Classics.h"

// Constructor for the Classics class
Classics::Classics(int stock, const string &director, const string &title,
                   const string &majorActor, int month, int year)
    : Movie(stock, director, title, majorActor, month, year) {}

// Get the movie type for the Classics class
string Classics::getMovieType() const { return "C"; }

// Get the media type for the Classics class
string Classics::getMediaType() const { return mediaType; }

// Overloaded equality operator for comparing Classics objects with other Movie
// objects
bool Classics::operator==(const Movie &other) const {
  return getMonth() == other.getMonth() && getYear() == other.getYear() &&
         getMajorActor() == other.getMajorActor();
}
void Classics::print(ostream &os) const {
  os << "C, " << getTitle() << ", " << getStock() << ", " << getDirector()
     << ", " << getMajorActor() << ", " << getMonth() << ", " << getYear();
}