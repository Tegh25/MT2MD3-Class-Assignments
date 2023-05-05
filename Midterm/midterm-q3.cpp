#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// class Deque uses vectors to implement deque data structure to store strings
class Deque {
 public: // public function definition
  Deque(int n);
  ~Deque();
  void insertFront(std::string e);
  void insertBack(std::string e);
  void eraseFront();
  void eraseBack();
  string front();
  string back();
  int size();
  bool empty();

 private: // vector of strings as main component of data structure
  vector<string> newDeque;
  int maxLength; // maxLength stores maximum size of deque
  int length; // length stores current size
};

Deque::Deque(int n) { // constructor
  vector<string> newDeque;
  newDeque.resize(n); // resizes vector to be maximum size, does not affect front, back, length, etc.
  maxLength = n;
  length = 0;
}

Deque::~Deque() { // destructor
  // delete newDeque;
}

void Deque::insertFront(std::string e) { // adds string to front of deque if deque is not full
  if (size() + 1 > maxLength) {
    cout << "The deque is at max capacity!\n";
  } else {
    newDeque.insert(newDeque.begin(), e);
    length++;
  }
}

void Deque::insertBack(std::string e) { // adds string to back of deque if deque is not full
  if (size() + 1 > maxLength) {
    cout << "The deque is at max capacity!\n";
  } else {
    newDeque.push_back(e);
    length++;
  }
}

void Deque::eraseFront() { // erases string at front of deque if deque is not empty
  if (size() > 0) {
    newDeque.erase(newDeque.begin());
    length--;
  }
  else {
    cout << "error: empty deque\n";
  }
}

void Deque::eraseBack() { // erases string at back of deque if deque is not empty
  if (size() > 0) {
    newDeque.erase(newDeque.begin() + size() - 1);
    length--;
  }
  else {
    cout << "error: empty deque\n";
  }
}

string Deque::front() { // returns front of deque as string if not empty
  if (size() > 0) {
    return newDeque.front();
  } else {
    return "error: empty deque\n";
  }
}

string Deque::back() { // returns back of deque as string if not empty
  if (size() > 0) {
    return newDeque.back();
  }
  return "error: empty deque\n";
}

int Deque::size() { // returns current size of deque as integer
  return length;
}

bool Deque::empty() { // returns boolean true if deque is empty, false if not
  if (size() > 0) {
    return false;
  }
  return true;
}