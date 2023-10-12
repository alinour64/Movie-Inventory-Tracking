#ifndef INVENTORY_H
#define INVENTORY_H

#include "Customer.h"
#include "HashTable.h"
#include "Movie.h"
#include <algorithm>
#include <vector>
using namespace std;

class Customer;
class Inventory {
private:
  vector<Movie *> movies;               // Vector to store movie pointers
  HashTable<int, Customer *> customers; // Hash table to store customer pointers

public:
  Inventory();                      // Constructor

  ~Inventory();                     // Destructor

  void addMovie(Movie *movie);      // Add a movie to the inventory
  void removeMovie(Movie *movie);   // Remove a movie from the inventory
  Movie *searchMovie(Movie *movie); // Search for a movie in the inventory
  void displayInventory() const;    // Display the inventory

  void displayCustomerHistory(
      int customerID);       // Display the borrowing history of a customer
  bool Borrow(Customer *customer,
              Movie *movie); // Borrow a movie for a customer
  bool Return(Customer *customer,
              Movie *movie); // Return a movie from a customer
  void addCustomer(Customer *customer);   // Add a customer to the inventory
  Customer *findCustomer(int customerId); // Find a customer by ID

private:
  void sortMovies(); // Sort the movies in the inventory
};

#endif
