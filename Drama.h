#ifndef DRAMA_H
#define DRAMA_H

#include "Movie.h"
#include <iostream>
#include <ostream>

using namespace std;

// Declaration of the Drama class, which is a derived class of Movie
class Drama : public Movie {
public:
  // Constructor
  Drama(int stock, const string &director, const string &title, int year);

  // Override the getMovieType() function from the base class
  virtual string getMovieType() const override;

  // Additional function specific to the Drama class
  virtual string getMediaType() const override;

  // Override the operator==() function from the base class
  virtual bool operator==(const Movie &other) const override;
  virtual void print(ostream &os) const override;
};

#endif
