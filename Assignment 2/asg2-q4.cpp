#include <cstdlib>
#include <iostream>
using namespace std;

template <typename E>  // forward declaration of SLinkedList
class SLinkedList;

template <typename E>
class SNode {  // singly linked list node
 private:
  E elem;                       // linked list element value
  SNode<E>* next;               // next item in the list
  friend class SLinkedList<E>;  // provide SLinkedList access
};

template <typename E>
class SLinkedList {  // a singly linked list
 public:
  SLinkedList();              // empty list constructor
  ~SLinkedList();             // destructor
  bool empty() const;         // is list empty?
  const E& front() const;     // return front element
  void addFront(const E& e);  // add to front of list
  void removeFront();
  int numNodes();                     // remove front of list
  int numNodes(SNode<E>* e, int n);   // returns length of list
  void print();                       // prints list
  void append(SLinkedList<E>& list);  // adds another list to end of list
  void reverse();                     // reverses list
  void reverse(SNode<E>* prevNode, SNode<E>* curNode,
               SNode<E>* nextNode);  // reverses list
 private:
  SNode<E>* head;  // head of the list
};

template <typename E>
SLinkedList<E>::SLinkedList()  // constructor
    : head(NULL) {}

template <typename E>
bool SLinkedList<E>::empty() const {  // is list empty?
  return head == NULL;
}

template <typename E>
const E& SLinkedList<E>::front() const {  // return front element
  return head->elem;
}

template <typename E>
SLinkedList<E>::~SLinkedList() {  // destructor
  while (!empty()) removeFront();
}

template <typename E>
void SLinkedList<E>::addFront(const E& e) {  // add to front of list
  SNode<E>* v = new SNode<E>;                // create new node
  v->elem = e;                               // store data
  v->next = head;                            // head now follows v
  head = v;                                  // v is now the head
}

template <typename E>
void SLinkedList<E>::removeFront() {  // remove front item
  if (head == NULL) return;
  SNode<E>* old = head;  // save current head
  head = old->next;      // skip over old head
  delete old;            // delete the old head
}

template <typename E>
int SLinkedList<E>::numNodes() {  // acts as default parameters for the numNodes
                                  // method, could not use object head as
                                  // default parameter
  return numNodes(head, 0);
}

template <typename E>
int SLinkedList<E>::numNodes(SNode<E>* e,
                             int n) {  // counts and returns the number of nodes
  if (e == NULL) { // base case if end of list is reached
    return n;
  } else {
    return numNodes(e->next, n + 1); // recursively traverses through list
  }
}

template <typename E>
void SLinkedList<E>::print() {  // prints the nodes in the list
  SNode<E>* cur = head;
  while (cur->next != NULL) { // traverses through list until last node reached
    std::cout << cur->elem << "->";
    cur = cur->next;
  }
  std::cout << cur->elem << endl; // prints last node without arrow 
  delete cur;
}

template <typename E>
void SLinkedList<E>::append(
    SLinkedList<E>& list) {  // appends list two to the end of list one
  SNode<E>* cur = head;
  while (cur->next != NULL) { // traverses through list until last node reached
    cur = cur->next;
  }
  cur->next = list.head; // sets the last node's next pointer to be the other list's head
  delete cur;
}

template <typename E>
void SLinkedList<E>::reverse() {  // acts as default parameters for the reverse
                                  // method, could not use object head as
                                  // default parameter
  reverse(head, head->next, head->next->next);
}

template <typename E>
void SLinkedList<E>::reverse(SNode<E>* prevNode, SNode<E>* curNode,
                             SNode<E>* nextNode) {  // reverses the list
  if (nextNode == NULL) { // base case if end of list is reached
    curNode->next = prevNode;
    head->next = NULL; // resets head node
    head = curNode;
  } else {
    curNode->next = prevNode; // reverses what node the next pointer is pointing to
    reverse(curNode, nextNode, nextNode->next);
  }
}

int main() {
  /* START OF TEST MAIN */
  cout << "List 1 has 4 nodes:" << endl;
  SLinkedList<std::string> sllOne;
  sllOne.addFront("four");
  sllOne.addFront("three");
  sllOne.addFront("two");
  sllOne.addFront("one");
  sllOne.print();

  cout << "List 2 has 3 nodes:" << endl;
  SLinkedList<std::string> sllTwo;
  sllTwo.addFront("seven");
  sllTwo.addFront("six");
  sllTwo.addFront("five");
  sllTwo.print();

  cout << "After appending list 2 to list 1, list 1 has 7 nodes:" << endl;
  sllOne.append(sllTwo);
  sllOne.print();

  cout << "After reversing list 1, it looks like this:" << endl;
  sllOne.reverse();
  sllOne.print();
  /* END OF TEST MAIN */
}
