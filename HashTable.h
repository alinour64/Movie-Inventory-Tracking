#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>
using namespace std;

// HashTable class template
template <typename Key, typename Value> class HashTable {
private:
  vector<list<pair<Key, Value>>>
      table; // Vector of linked lists to store key-value pairs
  function<int(const Key &)> hashFunction; // Function object for hashing keys

public:
  // Constructor that initializes the HashTable with a specified size and hash
  // function
  HashTable(int size, function<int(const Key &)> hashFunction)
      : table(size), hashFunction(move(hashFunction)) {}

  // Default constructor
  HashTable() = default;

  // Destructor
  ~HashTable() {
    deleteAllValues(); // Deletes all dynamically allocated values

    // Clears each bucket in the table
    for (auto &bucket : table) {
      bucket.clear();
    }
    table.clear(); // Clears the table
  }

  // Inserts a key-value pair into the hash table
  void insert(const Key &key, const Value &value) {
    int idx =
        hashFunction(key) % table.size(); // Calculate the index of the bucket
    for (auto &pair : table[idx]) {
      if (pair.first == key) { // If the key already exists, update the value
        pair.second = value;
        return;
      }
    }
    table[idx].push_back(
        {key, value}); // Add the new key-value pair to the bucket
  }

  // Removes a key-value pair from the hash table
  bool remove(const Key &key) {
    int idx =
        hashFunction(key) % table.size(); // Calculate the index of the bucket
    for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
      if (it->first ==
          key) { // If the key is found, erase the pair from the bucket
        table[idx].erase(it);
        return true;
      }
    }
    return false; // Key not found
  }

  // Checks if a key exists in the hash table
  bool contains(const Key &key) const {
    int idx =
        hashFunction(key) % table.size(); // Calculate the index of the bucket
    return any_of(
        table[idx].begin(), table[idx].end(),
        [&key](const pair<Key, Value> &pair) { return pair.first == key; });
  }

  // Overloaded subscript operator for accessing values using keys
  Value &operator[](const Key &key) {
    int idx =
        hashFunction(key) % table.size(); // Calculate the index of the bucket
    for (auto &pair : table[idx]) {
      if (pair.first ==
          key) { // If the key is found, return the corresponding value
        return pair.second;
      }
    }
    throw out_of_range("Key not found"); // Key not found
  }

  // Clears all buckets in the hash table
  void clear() {
    for (auto &bucket : table) {
      bucket.clear();
    }
  }

  // Deletes all dynamically allocated values in the hash table
  void deleteAllValues() {
    for (auto &bucket : table) {
      for (auto &pair : bucket) {
        delete pair.second;    // Delete the value
        pair.second = nullptr; // Set the value pointer to null
      }
      bucket.clear();
    }
  }

  // Iterator functions
  typename list<pair<Key, Value>>::iterator begin() {
    for (auto &bucket : table) {
      if (!bucket.empty()) {
        return bucket.begin();
      }
    }
    return end();
  }

  typename list<pair<Key, Value>>::iterator end() {
    return typename list<pair<Key, Value>>::iterator();
  }

  typename list<pair<Key, Value>>::const_iterator begin() const {
    for (const auto &bucket : table) {
      if (!bucket.empty()) {
        return bucket.begin();
      }
    }
    return end();
  }

  typename list<pair<Key, Value>>::const_iterator end() const {
    return typename list<pair<Key, Value>>::const_iterator();
  }
};

#endif
