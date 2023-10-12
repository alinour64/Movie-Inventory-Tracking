#ifndef MOVIEFACTORY_H
#define MOVIEFACTORY_H

#include "Classics.h"
#include "Comedy.h"
#include "Drama.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class MovieFactory {
public:
  // Method to create a Movie object based on the type
  static Movie *CreateMovie(const string &line);
  static Movie *CreateMovie(string movieType, int stock, const string &director,
                            const string &title, int year);
  static Movie *CreateMovie(string movieType, int stock, const string &director,
                            const string &title, const string &majorActor,
                            int month, int year);

private:
  // Helper functions
  static vector<string> splitLine(const string &line);
  static string trim(const string &str);
  static string extractAllButLastTwoWords(const string &sentence);
  static void extractMonthAndYear(const string &sentence, int &month,
                                  int &year);
};

#endif
