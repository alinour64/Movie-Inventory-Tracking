#include "Inventory.h"

Inventory::Inventory() : customers(10000, [](int key) { return key; }) {}

Inventory::~Inventory() {
  // Delete all movie objects
  for (Movie *movie : movies) {
    delete movie;
  }
  movies.clear();

  // Clear customer data
  customers.deleteAllValues();
  customers.clear();
}

void Inventory::addMovie(Movie *movie) {
  for (int i = 0; i < movies.size(); i++) {
    if (*movie == *movies[i]) {
      movies[i]->setStock(movie->getStock() + movies[i]->getStock());
      return;
    }
  }
  movies.push_back(movie);
  sortMovies();
}

void Inventory::addCustomer(Customer *customer) {
  customers.insert(customer->getCustomerID(), customer);
}

Customer *Inventory::findCustomer(int customerId) {
  if (customers.contains(customerId)) {
    return customers[customerId];
  }
  cerr << "Customer not found" << endl;
  return nullptr;
}

void Inventory::removeMovie(Movie *movie) {
  // Remove the movie from the inventory
  movies.erase(remove(movies.begin(), movies.end(), movie), movies.end());
}

Movie *Inventory::searchMovie(Movie *movie) {
  auto it = find(movies.begin(), movies.end(), movie);
  if (it != movies.end()) {
    return *it;
  }
  return nullptr;
}

void Inventory::displayInventory() const {
  // Display information for each movie in the inventory
  for (auto *movie : movies) {
    cout << *movie << endl;
  }
}

void Inventory::sortMovies() {
  sort(movies.begin(), movies.end(),
       [](const Movie *a, const Movie *b) -> bool {
         if (a->getMovieType() != b->getMovieType()) {
           // Sort by genre: Comedy ('F') < Drama ('D') < Classics ('C')
           return *a < *b;
         }

         // Sort within each genre based on specific criteria
         switch (a->getMovieType()[0]) {
         case 'F':
           if (a->getTitle() != b->getTitle()) {
             return a->getTitle() < b->getTitle();
           }
           return a->getYear() < b->getYear();
         case 'D':
           if (a->getDirector() != b->getDirector()) {
             return a->getDirector() < b->getDirector();
           }
           return a->getTitle() < b->getTitle();
         case 'C':
           if (a->getYear() != b->getYear()) {
             return a->getYear() < b->getYear();
           }
           if (a->getMonth() != b->getMonth()) {
             return a->getMonth() < b->getMonth();
           }
           return a->getMajorActor() < b->getMajorActor();
         default:
           return false;
         }
       });
}

bool Inventory::Borrow(Customer *customer, Movie *movie) {
  if (customer == nullptr) {
    return false; // Return false if the customer is null
  }

  // Iterate through the movies in the inventory
  for (int i = 0; i < movies.size(); i++) {
    if (*movie == *movies[i]) {
      if (!movies[i]->decreaseStock()) {
        return false; // Return false if stock cannot be decreased
      }
      movies[i]->setMediaType(movie->getMediaType());
      movie = movies[i]; // Update the movie pointer
      break;             // Exit the loop if the movie is found
    }
    if (i == movies.size() - 1) {
      cerr << "Movie not in inventory. Borrow Failed!"
           << endl; // Display error message if the movie is not found
      return false; // Return false if the movie is not in the inventory
    }
  }

  customer->borrowed(movie); // Update customer's borrowed movies

  // Create a new borrow transaction
  Transaction borrowTransaction = Transaction(
      "B", customer, movie, movie->getMediaType(), movie->getMovieType());

  customer->addTransaction(borrowTransaction); // Add the transaction to the
                                               // customer's transaction history

  return true; // Return true to indicate successful borrowing
}

bool Inventory::Return(Customer *customer, Movie *movie) {
  if (customer == nullptr) {
    return false; // Return false if the customer is null
  }

  // Iterate through the movies in the inventory
  for (int i = 0; i < movies.size(); i++) {
    if (*movie == *movies[i]) {
      if (!customer->isBorrowed(movie)) {
        cerr << "You are not borrowing the movie. Return Failed"
             << endl; // Display error message if the movie is not borrowed by
                      // the customer
        return false; // Return false if the movie is not borrowed by the
                      // customer
      }
      movie = movies[i]; // Update the movie pointer
      break;             // Exit the loop if the movie is found
    }
    if (i == movies.size() - 1) {
      cerr << "Movie not in inventory. Return Failed"
           << endl; // Display error message if the movie is not found
      return false; // Return false if the movie is not in the inventory
    }
  }
  customer->unBorrowed(movie); // Update customer's borrowed movies
  movie->increaseStock();      // Increase the stock of the returned movie

  // Create a new return transaction
  Transaction returnTransaction = Transaction(
      "R", customer, movie, movie->getMediaType(), movie->getMovieType());

  customer->addTransaction(returnTransaction); // Add the transaction to the
                                               // customer's transaction history

  return true; // Return true to indicate successful return
}
