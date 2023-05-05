#include <cstdlib>
#include <iostream>
using namespace std;

/*
Author: Teghveer Ateliey
Date created: Jan 21, 2023
Last modified: Jan 22, 2023
Purpose: To create a subclass of Progression that calculates the absolute progression of two integers
*/

class Progression {  //  a generic progression
 public:
  Progression(long f = 0)  // constructor
      : first(f), cur(f) {}
  virtual ~Progression(){};      // destructor
  void printProgression(int n);  // print the first n values
 protected:
  virtual long firstValue();  // reset
  virtual long nextValue();   // advance
 protected:
  long first;  // first value
  long cur;    // current value
};

void Progression::printProgression(int n) {  // print n values
  cout << firstValue();                      // print the first
  for (int i = 2; i <= n; i++)               // print 2 through n
    cout << ' ' << nextValue();
  cout << endl;
}

long Progression::firstValue() {  //  reset
  cur = first;
  return cur;
}
long Progression::nextValue() {  // advance
  return ++cur;
}

// absolute value progression is a subclass of Progression, takes two integers as input
class AbsProgression : public Progression {
 public:
  AbsProgression(int a = 2, int b = 200);  // default constructor with values of 2 and 200
 protected:
  virtual long nextValue();  // nextValue() function
 protected:
  int x;  // intialized values to used for progression
  int y;
};

AbsProgression::AbsProgression(int a, int b)  // constructor
    : Progression(b), x(a), y(b) {}

// nextValue() function calculates the absolute value of the difference of the prev two values 
long AbsProgression::nextValue() {
  cur = abs(x - y);
  x = y; // reassigns prev two values to calculate next value again
  y = cur;
  return cur;
}

// start of main function
int main() {
  // testing absolute progression class with default constructor 
  cout << "Absolute progression with default constructor:" << endl;
  Progression *ap = new AbsProgression();
  ap->printProgression(10);
  delete (ap);

  // testing absolute progression class with custom constructor 
  cout << "Absolute progression with custom constructor:" << endl;
  Progression *bp = new AbsProgression(3, 300);
  bp->printProgression(10);
  delete (bp);

  return EXIT_SUCCESS;
}  // end of main function