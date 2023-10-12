#include "Driver.h"

Driver::Driver(Inventory &inventory) : inv(inventory){};

void Driver::runCommands(string line) {
  if (line[0] == 'I') {
    // Display inventory
    cout << "------------------------------START "
            "INVENTORY------------------------------"
         << endl;
    inv.displayInventory();
    cout << "------------------------------END "
            "INVENTORY------------------------------"
         << endl;
  } else if (line[0] == 'H') {
    // Display customer's transaction history
    vector<string> theLine = splitLineIntoWords(line);
    if (theLine.size() >= 2) {
      int customerId = stoi(theLine[1]);
      Customer *customer = inv.findCustomer(customerId);
      if (customer != nullptr) {
        customer->displayHistory();
      } else {
        cout << "Customer not found." << endl;
      }
    }
  } else if (line[0] == 'B') {
    // Borrow movie
    vector<string> theLine = splitLineIntoWords(line);
    if (!theLine.empty()) {
      int customerID = stoi(theLine[1]);

      string movieType = theLine[2];
      string movieInfo;
      for (size_t i = 3; i < theLine.size(); i++) {
        movieInfo += theLine[i];
        if (i < theLine.size() - 1) {
          movieInfo += " ";
        }
      }
      string mediaType = extractMediaTypeFromMovieInfo(line);

      Movie *movie = nullptr;
      if (movieInfo[0] == 'F') {
        // Create Classic movie object
        string title = extractTitleFromMovieInfo(movieInfo, "F");
        int year = extractYearFromMovieInfo(movieInfo);
        movie = MovieFactory::CreateMovie("F", 0, "", title, year);
        movie->setMediaType(mediaType);
      } else if (movieInfo[0] == 'D') {
        // Create Drama movie object
        string director = extractDirectorFromMovieInfo(movieInfo);
        string title = extractTitleFromMovieInfo(movieInfo, "D");
        movie = MovieFactory::CreateMovie("D", 0, director, title, 0);
        movie->setMediaType(mediaType);
      } else if (movieInfo[0] == 'C') {
        // Create Comedy movie object
        ReleaseDate releaseDate = extractReleaseDateFromMovieInfo(movieInfo);
        string majorActor = extractMajorActorFromMovieInfo(movieInfo);
        movie = MovieFactory::CreateMovie("C", 0, "", "", majorActor,
                                          releaseDate.month, releaseDate.year);
        movie->setMediaType(mediaType);
      } else {
        cerr << "Invalid movie type" << endl;
      }
      if (movie != nullptr) {

        // Borrow the movie
        inv.Borrow(inv.findCustomer(customerID), movie);
        delete movie;
      }
    }
  } else if (line[0] == 'R') {
    // Return movie
    vector<string> theLine = splitLineIntoWords(line);
    if (!theLine.empty()) {
      int customerID = stoi(theLine[1]);

      string movieType = theLine[2];
      string movieInfo;
      for (size_t i = 3; i < theLine.size(); i++) {
        movieInfo += theLine[i];
        if (i < theLine.size() - 1) {
          movieInfo += " ";
        }
      }

      Movie *movie = nullptr;
      if (movieInfo[0] == 'F') {
        // Create Classic movie object
        string title = extractTitleFromMovieInfo(movieInfo, "F");
        int year = extractYearFromMovieInfo(movieInfo);
        movie = MovieFactory::CreateMovie("F", 0, "", title, year);
      } else if (movieInfo[0] == 'D') {
        // Create Drama movie object
        string director = extractDirectorFromMovieInfo(movieInfo);
        string title = extractTitleFromMovieInfo(movieInfo, "D");
        movie = MovieFactory::CreateMovie("D", 0, director, title, 0);
      } else if (movieInfo[0] == 'C') {
        // Create Comedy movie object
        ReleaseDate releaseDate = extractReleaseDateFromMovieInfo(movieInfo);
        string majorActor = extractMajorActorFromMovieInfo(movieInfo);
        movie = MovieFactory::CreateMovie("C", 0, "", "", majorActor,
                                          releaseDate.month, releaseDate.year);
      }

      if (movie != nullptr) {
        // Return the movie
        inv.Return(inv.findCustomer(customerID), movie);
        delete movie;
      } else {
        cout << "Invalid movie type." << endl;
      }
    }
  } else {
    cout << "Invalid command." << endl;
  }
}

vector<string> Driver::splitLineIntoWords(const string &line) {
  istringstream iss(line);
  vector<string> words(istream_iterator<string>{iss},
                       istream_iterator<string>());
  return words;
}

string Driver::extractTitleFromMovieInfo(const string &movieInfo,
                                         string movieType) {
  if (movieType == "F") {
    size_t firstSpacePos = movieInfo.find(" ");
    size_t firstCommaPos = movieInfo.find(",");
    if (firstSpacePos != string::npos && firstCommaPos != string::npos) {
      return movieInfo.substr(firstSpacePos + 1,
                              firstCommaPos - firstSpacePos - 1);
    }
  } else if (movieType == "D") {
    string movieLine = movieInfo;
    if (!movieLine.empty() && movieLine.back() == ',') {
      movieLine.pop_back();
    }
    size_t firstCommaPos = movieLine.find(",");
    if (firstCommaPos != string::npos) {
      size_t startOfTitle = movieLine.find_first_not_of(" ", firstCommaPos + 1);
      if (startOfTitle != string::npos) {
        return movieLine.substr(startOfTitle);
      }
    }
  }
  return "";
}

int Driver::extractYearFromMovieInfo(const string &movieInfo) {
  size_t commaPos = movieInfo.find(",");
  if (commaPos != string::npos) {
    string yearStr = movieInfo.substr(commaPos + 2);
    return stoi(yearStr);
  }
  return 0;
}

string Driver::extractDirectorFromMovieInfo(const string &movieInfo) {
  return extractTitleFromMovieInfo(movieInfo, "F");
}

ReleaseDate Driver::extractReleaseDateFromMovieInfo(const string &movieInfo) {
  stringstream ss(movieInfo);
  string token;
  ReleaseDate releaseDate;

  if (!(ss >> token)) {
    return {0, 0};
  }

  if (ss >> releaseDate.month >> releaseDate.year) {
    return releaseDate;
  }

  return {0, 0};
}

string Driver::extractMajorActorFromMovieInfo(const string &movieInfo) {
  istringstream iss(movieInfo);
  string token;

  for (int i = 0; i < 3; ++i) {
    if (!(iss >> token)) {
      return "";
    }
  }

  getline(iss, token);
  return token.substr(1);
}

string Driver::extractMediaTypeFromMovieInfo(const string &movieInfo) {
  istringstream iss(movieInfo);
  string word;
  int count = 0;
  while (iss >> word) {
    ++count;
    if (count == 3) {
      return word;
    }
  }
  return "";
}
