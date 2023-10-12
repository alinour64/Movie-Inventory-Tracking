#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;

class Movie {
public:
  // Constructors
  Movie(int stock, const string &director, const string &title, int year);
  Movie(int stock, const string &director, const string &title,
        const string &majorActor, int month, int year);

  // Destructor
  virtual ~Movie();

  // Pure virtual functions
  virtual string getMovieType() const = 0;
  virtual string getMediaType() const = 0;

  // Getter methods
  string getTitle() const;
  string getDirector() const;
  int getYear() const;
  int getStock() const;
  string getMajorActor() const;
  int getMonth() const;

  // Setter methods
  void setTitle(const string &newTitle);
  void setDirector(const string &newDirector);
  void setYear(int newYear);
  void setStock(int newStock);
  void setMajorActor(const string &newMajorActor);
  void setMonth(int newMonth);
  void setMediaType(const string &mediaType);

  // Stock management methods
  bool increaseStock();
  bool decreaseStock();

  // Comparison operator
  virtual bool operator==(const Movie &other) const = 0;
  virtual void print(ostream &os) const = 0; // Pure virtual function
  friend ostream &operator<<(ostream &os, const Movie &movie);
  bool operator<(const Movie &other) const;

protected:
  // Member variables
  int stock;
  string director;
  string title;
  string majorActor;
  string mediaType;
  int month;
  int year;
};

#endif
