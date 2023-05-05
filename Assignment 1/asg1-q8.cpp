#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

/*
Author: Teghveer Ateliey
Date created: Jan 20, 2023
Last modified: Jan 20, 2023
Purpose: To store pairs of values of any type using a class object
*/

// Pair class takes two of any type as input an stores them together
template <typename A, typename B>
class Pair {
 public:
  Pair(A a, B b);  // calling constructor for Pair
  ~Pair(){};       // destructor for Pair
  void print();    // print function
 private:
  A x;  // inputted variables are stored here with corresponding types
  B y;
};

template <typename A, typename B>
Pair<A, B>::Pair(A a, B b) {  // constructor which initializes storage
  x = a;  // storing inputted variables with corresponding types
  y = b;
}

// print() class function takes no arguments
// prints stored variables for class instance
template <typename A, typename B>
void Pair<A, B>::print() {  // variables can be of any type
  cout << "<" << x << ", " << y << ">" << endl;
}

// start of main function
int main() {
  Pair<int, double> p1(1, 7.3);
  p1.print();

  Pair<std::string, double> p2("hello", 7.7);
  p2.print();

  Pair<float, long> p3(1.2, 777777773);
  p3.print();

  return EXIT_SUCCESS;
}  // end of main function