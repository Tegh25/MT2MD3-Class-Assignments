#include <cstdlib>
#include <iostream>
using namespace std;

class Progression {  // a generic progression
 public:
  Progression(long f = 0)  // constructor
      : first(f), cur(f) {}
  virtual ~Progression(){};      // destructor
  void printProgression(int n);  // print the first n values
  virtual long nextValue();      // advance
 protected:
  virtual long firstValue();  // reset
 protected:
  long first;  // first value
  long cur;    // current value
};

void Progression::printProgression(int n) {  // print n values
  cout << firstValue();                      // print the first
  for (int i = 2; i <= n; i++)               // print 2 through n
    cout << " " << nextValue();
  cout << endl;
}

long Progression::firstValue() {  // reset
  cur = first;
  return cur;
}

long Progression::nextValue() {  // advance
  return ++cur;
}

class GeomProgression : public Progression {  // geometric progression
 public:
  GeomProgression(long b = 2);  // constructor
 public:
  virtual long nextValue();  // advance
 protected:
  long base;  // base value
};

GeomProgression::GeomProgression(long b)  // constructor
    : Progression(1), base(b) {}

long GeomProgression::nextValue() {  // advance by multiplying
  cur *= base;
  return cur;
}

int main() {
  Progression *p = new GeomProgression();
  Progression *sp = dynamic_cast<Progression *>(p);
  // cout << sp->nextValue() << endl;
  cout << p->nextValue() << endl;
  sp->printProgression(5);
  p->printProgression(5);

  // TB page 103

  return EXIT_SUCCESS;
}