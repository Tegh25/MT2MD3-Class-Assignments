#include <cstdlib>
#include <iostream>
using namespace std;

typedef std::string Elem;

class DNode {  // doubly linked list node
 private:
  Elem name;  // node element value
  int score;
  DNode* prev;               // previous node in list
  DNode* next;               // next node in list
  friend class DLinkedList;  // allow DLinkedList access
};

class DLinkedList {  // doubly linked list
 public:
  DLinkedList();                  // constructor
  DLinkedList(DLinkedList& dll);  // copy constructor
  ~DLinkedList();                 // destructor
  bool empty() const;             // is list empty?
  const Elem& front() const;      // get front element
  const Elem& back() const;       // get back element
  void AddScoreInOrder(const Elem& newName,
                       int newScore);  // adds score in order
  void removeFront();                  // remove from front
  void removeBack();                   // remove from back
  void RemoveScore(int index); // removes score at index
  bool UpdateScore(std::string name, int score); // updates score of player if exists
  int Size(); // helper method for size
  int Size(DNode* e, int n); // returns size of list
  void Print(); // helper method for size
  void Print(DNode* e); // prints list
  void operator=(DLinkedList& dll); // overload operator

 private:         // local type definitions
  DNode* header;  // list sentinels
  DNode* trailer;

 protected:  // local utilities
  void add(DNode* v, const Elem& newName,
           int newScore);  // insert new node before v
  void remove(DNode* v);   // remove node v
};

DLinkedList::DLinkedList() {  // constructor
  header = new DNode;         // create sentinels
  trailer = new DNode;
  header->next = trailer;  // have them point to each other
  trailer->prev = header;
  header->prev = NULL;
  trailer->next = NULL;
}

DLinkedList::DLinkedList(DLinkedList& dll) {  // copy constructor
  header = new DNode;                         // create sentinels
  trailer = new DNode;
  header->next = trailer;  // have them point to each other
  trailer->prev = header;
  header->prev = NULL;
  trailer->next = NULL;

  DNode* node = dll.header->next;  // sets nodes to traverse through list
  DNode* cur = header;

  int size = dll.Size();  // gets size of original list

  for (int i = 0; i < size; i++) {  // traverses through original list and adds
                                    // to copied list in same order
    add(cur, node->name, node->score);
    node = node->next;
    cur = cur->next;
  }
}

DLinkedList::~DLinkedList() {  // destructor
  while (!empty()) {
    removeFront();  //  remove all but sentinels
  }
  delete header;  //  remove the sentinels
  delete trailer;
}

bool DLinkedList::empty() const {  // is list empty?
  return (header->next == trailer);
}

const Elem& DLinkedList::front() const {  // get front element
  return header->next->name;
}

const Elem& DLinkedList::back() const {  // get back element
  return trailer->prev->name;
}

void DLinkedList::add(DNode* x, const Elem& newName,
                      int newScore) {  // insert new node after v, included with
                                       // DLinkedList template
  DNode* newNode = new DNode;
  newNode->name = newName;
  newNode->score = newScore;
  newNode->next = x->next;
  newNode->prev = x;
  x->next->prev = newNode;
  x->next = newNode;
}

void DLinkedList::AddScoreInOrder(
    const Elem& newName,
    int newScore) {  // adds score and maintains numerical order
  DNode* cur = header;
  while (cur->next != trailer &&
         cur->next->score >=
             newScore) {  // traverses through list until end reached our a node
                          // with a lower score is found
    cur = cur->next;
  }
  add(cur, newName,
      newScore);  // add method adjusts pointers and adds correct node
}

void DLinkedList::remove(DNode* v) {  // remove node v
  DNode* u = v->prev;                 // predecessor
  DNode* w = v->next;                 // successor
  u->next = w;                        // unlink v from list
  w->prev = u;
  delete v;
}

void DLinkedList::removeFront() {  // remove from font
  remove(header->next);
}

void DLinkedList::removeBack() {  // remove from back
  remove(trailer->prev);
}

void DLinkedList::RemoveScore(int index) {  // removes score at a certain index
  DNode* cur = header->next;  // initialize pointer to traverse through list
  for (int i = 0; i < index; i++) {
    cur = cur->next;
  }
  remove(cur);  // remove function reassigns pointers and deletes node in list
}

bool DLinkedList::UpdateScore(
    std::string name,
    int score) {  // updates score of a single player if their name is found
  DNode* cur = new DNode;
  cur = header->next;
  while (cur != trailer) {    // iterates through list
    if (cur->name == name) {  // updates score and returns true if name is found
      cur->score = score;
      return true;
    }
    cur = cur->next;  // increments pointer traversing through list
  }
  return false;  // if name is not found
}

int DLinkedList::Size() {
  return Size(header->next, 0);
}  // helper method for default paramaters

int DLinkedList::Size(DNode* e,
                      int n) {  // counts and returns the number of nodes
  if (e == trailer) {           // base case if end of list is reached
    return n;
  } else {
    return Size(e->next, n + 1);  // recursively traverses through list
  }
}

void DLinkedList::Print() {
  Print(header->next);
}  // helper method for default paramaters

void DLinkedList::Print(DNode* e) {  // prints contents of list recursively
  if (e->next == trailer) {  // base case for when last index of list is reached
    cout << "{" << e->name << "," << e->score << "}" << endl;
  } else {  // recursively traverses through list
    cout << "{" << e->name << "," << e->score << "}"
         << "->";
    Print(e->next);
  }
}

void DLinkedList::operator=(
    DLinkedList& dll) {  // overload operator function to copy objects
  header = new DNode;    // create sentinels
  trailer = new DNode;
  header->next = trailer;  // have them point to each other
  trailer->prev = header;
  header->prev = NULL;
  trailer->next = NULL;

  DNode* node = dll.header->next;  // sets nodes to traverse through list
  DNode* cur = header;

  int size = dll.Size();  // gets size of original list

  for (int i = 0; i < size; i++) {  // traverses through original list and adds
                                    // to copied list in same order
    add(cur, node->name, node->score);
    node = node->next;
    cur = cur->next;
  }
}

int main() {
  DLinkedList scores;
  scores.AddScoreInOrder("Jeff", 7);
  scores.AddScoreInOrder("Jen", 9);
  scores.AddScoreInOrder("Ilya", 3);
  scores.AddScoreInOrder("Sara", 10);
  scores.AddScoreInOrder("Sam", 11);
  // Test size function
  cout << "Number of scores is " << scores.Size() << endl;
  scores.Print();
  // Test remove function
  scores.RemoveScore(3);
  cout << "Number of scores is now " << scores.Size() << endl;
  scores.Print();
  // Test update function
  if (scores.UpdateScore("Jeff", 6)) scores.Print();
  // Test copy constructor
  DLinkedList scores_copy_1(scores);
  scores.UpdateScore("Jen", 5);
  scores.Print();
  scores_copy_1.Print();
  // Test assignment operator overload
  DLinkedList scores_copy_2 = scores_copy_1;
  scores_copy_1.UpdateScore("Jen", 5);
  scores_copy_1.Print();
  scores_copy_2.Print();
}