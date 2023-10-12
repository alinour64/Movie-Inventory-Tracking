#ifndef COMEDY_H
#define COMEDY_H

#include "Movie.h"
#include <iostream>
#include <ostream>

using namespace std;

// Declaration of the Comedy class derived from the Movie class
class Comedy : public Movie {
public:
  // Constructor for the Comedy class
  Comedy(int stock, const string &director, const string &title, int year);

  // Overriding the getMovieType function from the base class
  virtual string getMovieType() const override;

  // Overriding the getMediaType function from the base class
  virtual string getMediaType() const override;

  // Overriding the equality operator to compare Comedy objects
  virtual bool operator==(const Movie &other) const override;
  virtual void print(ostream &os) const override;
};

#endif
