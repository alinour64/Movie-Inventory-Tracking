# Self-Evaluation

## Name(s):

Out of 25 points. Use output.txt created using
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run,
  the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: 0

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: fully
History: fully
Borrow: fully
Return: fully

Q: -1 for each compilation warning, min -3: 0

- Check under _1. Compiles without warnings_
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 0

- Check under _3. clang-tidy warnings_
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 0

- Check under _4. clang-format does not find any formatting issues_

Q: -2 for any detected memory leak: 0

- Check under _5. No memory leaks using g++_
- Check under _6. No memory leaks using valgrind_

Q: Do the tests sufficiently test the code: 0

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under _7. Tests have full code coverage_ paying attention to _The lines below were never executed_

Q: Are all functions in .h and .cpp file documents (min -3): 0

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: Driver.cpp

invalid movie type: MovieFactory.cpp

invalid customer ID: Inventory.cpp

invalid movie: Inventory.cpp

factory classes: MovieFactory.cpp

hashtable: Inventory.cpp Used to store customers

container used for comedy movies: vector

function for sorting comedy movies: sortMovies();

function where comedy movies are sorted: Inventory::addMovie(Movie \*movie)

functions called when retrieving a comedy movie based on title and year: Inventory::searchMovie(Movie \*movie)

functions called for retrieving and printing customer history: Customer::displayHistory() const

container used for customer history: vector

functions called when borrowing a movie: Inventory::Borrow(Customer *customer, Movie *movie)

explain borrowing a movie that does not exist: search for movie, if reached end of vector print error message, return false so nothing is added in transactions

explain borrowing a movie that has 0 stock: attempt to decrease stock, if stock at 0 already false is returned, error message is printed and function is terminated by returning false

explain returning a movie that customer has not checked out: Search vector of movies of customer. If movie is not found error message is printed and function is terminated with return false

any static_cast or dynamic_cast used: No

Q: Total points: 25 (max 25)
