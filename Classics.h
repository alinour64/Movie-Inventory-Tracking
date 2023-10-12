#ifndef CLASSICS_H
#define CLASSICS_H

#include "Movie.h"
#include <iostream>
#include <ostream>
using namespace std;

// Declaration of the 'Classics' class, derived from the 'Movie' class
class Classics : public Movie {
public:
  // Constructor for the 'Classics' class
  Classics(int stock, const string &director, const string &title,
           const string &majorActor, int month, int year);

  // Override of the 'getMovieType' function from the base class
  virtual string getMovieType() const override;

  // Override of the 'getMediaType' function from the base class
  virtual string getMediaType() const override;

  // Override of the '==' operator for comparing 'Classics' objects
  virtual bool operator==(const Movie &other) const override;
  virtual void print(ostream &os) const override;
};

#endif
