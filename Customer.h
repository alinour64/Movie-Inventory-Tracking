#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Inventory.h"
#include "Movie.h"
#include "Transaction.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Transaction;

// The Customer class represents a customer who can borrow and return movies.
class Customer {
public:
  // Constructor to initialize a Customer object with the given ID, last name,
  // and first name.
  Customer(int customerID, const string &lastName, const string &firstName);
  explicit Customer(string line);
  // Vector to store the transactions made by the customer.
  vector<Transaction> transactions = {};

  // Vector to store the movies currently borrowed by the customer.
  vector<Movie *> moviesBorrowed = {};

  // Destructor to clean up resources when a Customer object is destroyed.
  ~Customer();

  // Accessor methods to retrieve the customer's ID, last name, and first name.
  int getCustomerID() const;
  string getLastName() const;
  string getFirstName() const;

  // Method to add a transaction to the customer's transaction history.
  void addTransaction(const Transaction &transaction);

  // Method to retrieve the customer's transaction history.
  const vector<Transaction> &getTransactions() const;

  // Method to display the customer's transaction history.
  void displayHistory() const;

  // Method to add a movie to the list of movies borrowed by the customer.
  void borrowed(Movie *movie);

  // Method to remove a movie from the list of movies borrowed by the customer.
  void unBorrowed(Movie *movie);

  // Method to check if a movie is currently borrowed by the customer.
  bool isBorrowed(Movie *movie);

private:
  // Member variables to store the customer's ID, last name, and first name.
  int customerID;
  string lastName;
  string firstName;
};

#endif
