#include "Customer.h"

Customer::Customer(int customerID, const string &lastName,
                   const string &firstName)
    : customerID(customerID), lastName(lastName), firstName(firstName) {}

Customer::~Customer() {
  // Clear the vectors storing borrowed movies and transactions
  moviesBorrowed.clear();
  transactions.clear();
}

int Customer::getCustomerID() const { return customerID; }

string Customer::getLastName() const { return lastName; }

string Customer::getFirstName() const { return firstName; }

void Customer::addTransaction(const Transaction &transaction) {
  // Add a transaction to the list
  transactions.push_back(transaction);
}

const vector<Transaction> &Customer::getTransactions() const {
  // Return the list of transactions
  return transactions;
}

void Customer::borrowed(Movie *movie) {
  // Add a borrowed movie to the list
  moviesBorrowed.push_back(movie);
}

void Customer::unBorrowed(Movie *movie) {
  for (int i = 0; i < moviesBorrowed.size(); i++) {
    if (*moviesBorrowed[i] == *movie) {
      // Remove the borrowed movie from the list
      moviesBorrowed.erase(moviesBorrowed.begin() + i);
      break;
    }
  }
}

bool Customer::isBorrowed(Movie *movie) {
  for (int i = 0; i < moviesBorrowed.size(); i++) {
    if (*movie == *moviesBorrowed[i]) {
      return true;
    }
  }
  return false;
}

void Customer::displayHistory() const {
  cout << "Transaction History for Customer " << customerID << ": " << firstName
       << " " << lastName << endl;
  if (transactions.empty()) {
    cout << "No transactions found." << endl;
    return;
  }
  for (const Transaction &transaction : transactions) {
    // Display each transaction in the history
    transaction.display();
  }
  cout << endl;
}
