#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Customer.h"
#include "Movie.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer; // Forward declaration of Customer class

class Transaction {
public:
  // Constructor
  Transaction(string type, const Customer *customer, const Movie *movie,
              string mediaType, string movieType);

  // Getter methods
  string getType() const;
  const Customer *getCustomer() const;
  const Movie *getMovie() const;

  // Display method
  void display() const;

private:
  string type;              // Type of transaction
  const Customer *customer; // Pointer to the associated customer
  const Movie *movie;       // Pointer to the associated movie
  string mediaType;         // Type of media
  string movieType;         // Type of movie
};

#endif
