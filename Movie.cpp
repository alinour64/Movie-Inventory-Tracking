#include "Movie.h"
#include <iostream>
using namespace std;

Movie::Movie(int stock, const string &director, const string &title, int year)
    : stock(stock), director(director), title(title), year(year) {}

Movie::Movie(int stock, const string &director, const string &title,
             const string &majorActor, int month, int year)
    : stock(stock), director(director), title(title), majorActor(majorActor),
      month(month), year(year) {}

// Destructor
Movie::~Movie() {}

// Getters
string Movie::getTitle() const { return title; }

string Movie::getDirector() const { return director; }

int Movie::getYear() const { return year; }

int Movie::getStock() const { return stock; }

string Movie::getMajorActor() const { return majorActor; }

int Movie::getMonth() const { return month; }

// Setters
void Movie::setTitle(const string &newTitle) { title = newTitle; }

void Movie::setDirector(const string &newDirector) { director = newDirector; }

void Movie::setYear(int newYear) { year = newYear; }

void Movie::setStock(int newStock) {
  if (newStock >= 0) {
    stock = newStock;
  } else {
    stock = 0;
  }
}

void Movie::setMediaType(const string &newMediaType) {
  mediaType = newMediaType;
}

void Movie::setMajorActor(const string &newMajorActor) {
  majorActor = newMajorActor;
}

void Movie::setMonth(int newMonth) { month = newMonth; }

// Stock operations
bool Movie::increaseStock() {
  setStock(getStock() + 1);
  return true;
}

bool Movie::decreaseStock() {
  if (getStock() <= 0) {
    cerr << "There is no more stock. Borrow Failed" << endl;
    return false;
  }
  setStock(getStock() - 1);
  return true;
}
ostream &operator<<(ostream &os, const Movie &movie) {
  movie.print(os); // Will call the correct function thanks to polymorphism
  return os;
}
bool Movie::operator<(const Movie &other) const {
  // Sort by genre: Comedy ('F') < Drama ('D') < Classics ('C')
  if (getMovieType() != other.getMovieType()) {
    return getMovieType() == "F" ||
           (getMovieType() == "D" && other.getMovieType() == "C");
  }

  // Sort within the same genre based on specific criteria
  switch (getMovieType()[0]) {
  case 'F':
    if (getTitle() != other.getTitle()) {
      return getTitle() < other.getTitle();
    }
    return getYear() < other.getYear();
  case 'D':
    if (getDirector() != other.getDirector()) {
      return getDirector() < other.getDirector();
    }
    return getTitle() < other.getTitle();
  case 'C':
    if (getYear() != other.getYear()) {
      return getYear() < other.getYear();
    }
    if (getMonth() != other.getMonth()) {
      return getMonth() < other.getMonth();
    }
    return getMajorActor() < other.getMajorActor();
  default:
    return false;
  }
}
