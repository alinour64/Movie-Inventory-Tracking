#include "Transaction.h"

// Constructor
Transaction::Transaction(string type, const Customer *customer,
                         const Movie *movie, string mediaType, string movieType)
    : type(type), customer(customer), movie(movie), mediaType(mediaType),
      movieType(movieType) {}

// Getter for the type of transaction
string Transaction::getType() const { return type; }

// Getter for the customer associated with the transaction
const Customer *Transaction::getCustomer() const { return customer; }

// Getter for the movie associated with the transaction
const Movie *Transaction::getMovie() const { return movie; }

// Display the transaction details
void Transaction::display() const {
  cout << getType() << " ";
  // Check if the customer is not null and display the customer ID
  if (customer != nullptr) {
    cout << getCustomer()->getCustomerID() << " ";
  } else {
    cout << " N/A ";
  }

  cout << mediaType << " ";

  // Check if the movie is not null and display the movie details
  if (movie != nullptr) {
    cout << *movie;
  } else {
    cout << " N/A ";
  }
  cout << endl;
}
