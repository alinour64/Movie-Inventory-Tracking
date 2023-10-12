#ifndef DRIVER_H
#define DRIVER_H

#include "Inventory.h"
#include "Movie.h"
#include "MovieFactory.h"
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Structure to represent a release date
struct ReleaseDate {
  int month;
  int year;
};

// Driver class responsible for executing commands and interacting with the
// inventory
class Driver {
private:
  Inventory &inv; // Reference to the inventory

public:
  // Constructor that takes a reference to an Inventory object
  explicit Driver(Inventory &inventory);

  // Static method to split a line into words and return them in a vector
  static vector<string> splitLineIntoWords(const string &line);

  // Static method to extract the major actor from movie information
  static string extractMajorActorFromMovieInfo(const string &movieInfo);

  // Static method to extract the release date from movie information
  static ReleaseDate extractReleaseDateFromMovieInfo(const string &movieInfo);

  // Static method to extract the director from movie information
  static string extractDirectorFromMovieInfo(const string &movieInfo);

  // Static method to extract the year from movie information
  static int extractYearFromMovieInfo(const string &movieInfo);

  // Static method to extract the title from movie information, given the movie
  // type
  static string extractTitleFromMovieInfo(const string &movieInfo,
                                          string movieType);

  // Static method to extract the media type from movie information
  static string extractMediaTypeFromMovieInfo(const string &movieInfo);

  // Method to run commands passed as a string
  void runCommands(string line);
};

#endif
