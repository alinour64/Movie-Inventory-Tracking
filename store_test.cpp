/**
 * Testing ass4 movie store functions
 *
 * @author Yusuf Pisan
 * @date 19 Jan 2019
 */

#include "Driver.h"
#include "Inventory.h"
#include "Movie.h"
#include "MovieFactory.h"
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Function declarations
void readMovies();
void readCustomers();
void readCommands();

/**
 * Test function for the first store test.
 */
void testStore1() {
  cout << "Start testStore1" << endl;
  Inventory inv1;
  Driver driver1(inv1);
  // Create movies
  Movie *movie1 = MovieFactory::CreateMovie(
      "C, 10, Michael Curtiz, Casablanca, Ingrid Bergman 8 1942");
  Movie *movie2 = MovieFactory::CreateMovie(
      "D, 0, Steven Spielberg, Schindler's List, 1993");

  // Add movies to the inventory
  inv1.addMovie(movie1);
  inv1.addMovie(movie2);

  // Create customers
  Customer *customer1 = new Customer(1111, "Mouse", "Mickey");
  Customer *customer2 = new Customer(9999, "Duck", "Daffy");

  // Add customers
  inv1.addCustomer(customer1);
  inv1.addCustomer(customer2);

  // Test inventory command
  driver1.runCommands("I");

  // Test history command for a customer
  driver1.runCommands("H 1111");

  // Test borrow command for a movie available in the inventory
  driver1.runCommands("B 1111 D C 8 1942 Ingrid Bergman");

  // Test borrow command for a movie not available in the inventory
  driver1.runCommands("B 1111 D C 1 1900 Nonexistent Movie");
  // Test borrow command for a movie with 0 stock
  driver1.runCommands("B 1111 D D Steven Spielberg, Schindler's List");

  driver1.runCommands("H 1111");

  driver1.runCommands("I");
  cout << "End testStore1" << endl;
}

/**
 * Test function for the second store test.
 */
void testStore2() {
  cout << "Start testStore2" << endl;
  Inventory inv2;
  Driver driver2(inv2);
  // Create movie
  Movie *movie = MovieFactory::CreateMovie(
      "F, 10, Nora Ephron, Sleepless in Seattle, 1993");

  // Add movie to the inventory
  inv2.addMovie(movie);
  driver2.runCommands("I");

  // Create customer
  Customer *customer = new Customer(1000, "Mouse", "Minnie");

  // Add customer
  inv2.addCustomer(customer);

  // Test borrow command for a movie available in the inventory
  driver2.runCommands("B 1000 D F Sleepless in Seattle, 1993");
  driver2.runCommands("H 1000");
  // Test return command for a movie not borrowed
  driver2.runCommands("R 1000 D F Casablanca, 1942");

  // Test return command for a movie borrowed
  driver2.runCommands("R 1000 D F Sleepless in Seattle, 1993");

  // Test history command for a customer
  driver2.runCommands("H 1000");

  // Test invalid command code
  driver2.runCommands("X 1000 D C 8 1942 Ingrid Bergman");

  // Test invalid movie type
  driver2.runCommands("B 1000 D Y 2 1971 Ruth Gordon");

  // Test invalid customer ID
  driver2.runCommands("B 1234 D F Sleepless in Seattle, 1993");
  driver2.runCommands("I");

  cout << "End testStore2" << endl;
}
/**
 * Test function for the third store test.
 */
void testStore3() {
  cout << "Start testStore3" << endl;

  Inventory inv3;
  Driver driver3(inv3);

  // Create Drama movie
  Movie *movie = MovieFactory::CreateMovie(
      "D, 10, Steven Spielberg, Schindler's List, 1993");

  // Add movie to the inventory
  inv3.addMovie(movie);
  driver3.runCommands("I");

  // Create customer
  Customer *customer = new Customer(1111, "Mouse", "Mickey");

  // Add customer
  inv3.addCustomer(customer);

  // Test borrow command for a movie available in the inventory
  driver3.runCommands("B 1111 D D Steven Spielberg, Schindler's List");

  // Test return command for a movie not borrowed
  driver3.runCommands("R 1111 D D Some Other Director, Some Other Movie");

  // Test return command for a movie borrowed
  driver3.runCommands("R 1111 D D Steven Spielberg, Schindler's List");
  // Test return command for a movie previously borrowed but already returned
  driver3.runCommands("R 1111 D D Steven Spielberg, Schindler's List");

  // Test history command for a customer
  driver3.runCommands("H 1111");

  // Test invalid command code
  driver3.runCommands("X 1111 D C 8 1942 Ingrid Bergman");

  // Test invalid movie type
  driver3.runCommands("B 1111 D Y 2 1971 Ruth Gordon");

  // Test invalid customer ID
  driver3.runCommands("B 1234 D D Steven Spielberg, Schindler's List");
  driver3.runCommands("I");

  cout << "End testStore3" << endl;
}

/**
 * Test function for the final store test.
 */
void testStoreFinal() {
  cout << "=====================================" << endl;
  cout << "Start testStoreFinal" << endl;
  // Read movies, customers, and commands
  readMovies();
  readCustomers();
  readCommands();
  cout << "End testStoreFinal" << endl;
  cout << "=====================================" << endl;
}

/**
 * Executes all the tests.
 */
void testAll() {
  testStore1();
  testStore2();
  testStore3();
  testStoreFinal();
}
Inventory inv;
Driver driver(inv);
Customer *customer;
/**
 * Reads customer data from a file and adds customers to the inventory.
 */
void readCustomers() {
  ifstream file("data4customers.txt");
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      if (!line.empty()) {
        vector<string> customerInfo = Driver::splitLineIntoWords(line);

        if (customerInfo.size() >= 3) {
          string id = customerInfo[0];
          string last = customerInfo[1];
          string first = customerInfo[2];

          customer = new Customer(stoi(id), last, first);
          inv.addCustomer(customer);
        } else {
          cout << "Invalid line format: " << line << endl;
        }
      }
    }

    file.close();
  } else {
    cout << "Failed to open file." << endl;
  }
}

/**
 * Reads movie data from a file and adds movies to the inventory.
 */
void readMovies() {
  ifstream file("data4movies.txt");

  if (!file) {
    cerr << "Unable to open file data4movies.txt";
    exit(1);
  }

  string line;
  while (getline(file, line)) {
    if (!line.empty()) {
      Movie *movie = MovieFactory::CreateMovie(line);
      if (movie != nullptr) {
        inv.addMovie(movie);
      }
    }
  }

  file.close();
}

/**
 * Reads commands from a file and runs them using the driver.
 */
void readCommands() {
  string cfile = "data4commands.txt";
  ifstream fs(cfile);
  assert(fs.is_open());

  string line;
  while (getline(fs, line)) {
    if (!line.empty()) {
      driver.runCommands(line);
    }
  }

  fs.close();
}