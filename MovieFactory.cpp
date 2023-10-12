#include "MovieFactory.h"

// Create a movie based on the given line
Movie *MovieFactory::CreateMovie(const string &line) {
  vector<string> components = splitLine(line);

  if (line[0] == 'C') {
    // Extract month and year from the line
    int month;
    int year;
    extractMonthAndYear(components[4], month, year);

    // Extract major actor from the line
    string majorActor = extractAllButLastTwoWords(components[4]);

    // Create and return a new Classics movie object
    return new Classics(stoi(components[1]), trim(components[2]),
                        trim(components[3]), trim(majorActor), month, year);
  }
  if (line[0] == 'F') {
    // Create and return a new Comedy movie object
    return new Comedy(stoi(components[1]), trim(components[2]),
                      trim(components[3]), stoi(components[4]));
  }
  if (line[0] == 'D') {
    // Create and return a new Drama movie object
    return new Drama(stoi(components[1]), trim(components[2]),
                     trim(components[3]), stoi(components[4]));
  }

  // If the movie type is not recognized, print an error message and return
  // nullptr
  cerr << "Invalid movie type" << endl;
  return nullptr;
}

// Create a Comedy or Drama movie based on the given parameters
Movie *MovieFactory::CreateMovie(string movieType, int stock,
                                 const string &director, const string &title,
                                 int year) {
  if (movieType == "F") {
    // Create and return a new Comedy movie object
    return new Comedy(stock, trim(director), trim(title), year);
  }
  if (movieType == "D") {
    // Create and return a new Drama movie object
    return new Drama(stock, trim(director), trim(title), year);
  }

  // If the movie type is not recognized, print an error message and return
  // nullptr
  cerr << "Invalid movie type" << endl;
  return nullptr;
}

// Create a Classics movie based on the given parameters
Movie *MovieFactory::CreateMovie(string movieType, int stock,
                                 const string &director, const string &title,
                                 const string &majorActor, int month,
                                 int year) {
  if (movieType == "C") {
    // Create and return a new Classics movie object
    return new Classics(stock, trim(director), trim(title), trim(majorActor),
                        month, year);
  }

  // If the movie type is not recognized, print an error message and return
  // nullptr
  cerr << "Invalid movie type" << endl;
  return nullptr;
}

// Split the given line into components based on comma separator
vector<string> MovieFactory::splitLine(const string &line) {
  vector<string> components;
  stringstream ss(line);
  string component;
  while (getline(ss, component, ',')) {
    components.push_back(trim(component));
  }
  return components;
}

// Trim leading and trailing spaces from the given string
string MovieFactory::trim(const string &str) {
  string trimmedStr = str;

  // Trim leading spaces
  size_t start = trimmedStr.find_first_not_of(" ");
  if (start != string::npos) {
    trimmedStr = trimmedStr.substr(start);
  }

  // Trim trailing spaces
  size_t end = trimmedStr.find_last_not_of(" ");
  if (end != string::npos) {
    trimmedStr = trimmedStr.substr(0, end + 1);
  }

  return trimmedStr;
}

// Extract all words from the given sentence except the last two
string MovieFactory::extractAllButLastTwoWords(const string &sentence) {
  istringstream iss(sentence);
  string word;
  string extractedText;

  vector<string> words;
  while (iss >> word) {
    words.push_back(word);
  }

  int numWords = words.size();
  if (numWords > 2) {
    for (int i = 0; i < numWords - 2; ++i) {
      extractedText += words[i] + " ";
    }
  }

  return extractedText;
}

// Extract month and year from the given sentence
void MovieFactory::extractMonthAndYear(const string &sentence, int &month,
                                       int &year) {
  istringstream iss(sentence);
  string word;
  vector<string> words;
  while (iss >> word) {
    words.push_back(word);
  }

  int numWords = words.size();
  if (numWords >= 2) {
    month = stoi(words[numWords - 2]);
    year = stoi(words[numWords - 1]);
  }
}
