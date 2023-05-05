#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

typedef string Elem;  // base element type
class LinkedBinaryTree {
 protected:
  // insert Node declaration here. . .
  typedef string Elem;                                        // element type
  struct Node {                                            // a node of the tree
    Elem elt;                                              // element value
    Node *par;                                             // parent
    Node *left;                                            // left child
    Node *right;                                           // right child
    Node() : elt(), par(NULL), left(NULL), right(NULL) {}  // constructor
  };

 public:
  class Position {  // position in the tree
   private:
    Node *v;  // pointer to the node
   public:
    Position(Node *v = NULL) : v(v) {}  // constructor
    Node* GetNode() {
      return v;
    }
    Elem &operator*()                   // get element
    {
      return v->elt;
    }
    Position left() const  // get left child
    {
      return Position(v->left);
    }
    Position right() const  // get right child
    {
      return Position(v->right);
    }
    Position parent() const  // get parent
    {
      return Position(v->par);
    }
    bool isRoot() const  // root of the tree?
    {
      return v->par == NULL;
    }
    bool isExternal() const  // an external node?
    {
      return v->left == NULL && v->right == NULL;
    }
    friend class LinkedBinaryTree;  // give tree access
  };
  typedef std::list<Position>
      PositionList;  // list of positions
                     // insert Position declaration here. . .
 public:
  LinkedBinaryTree();              // constructor
  ~LinkedBinaryTree();             // destructor
  LinkedBinaryTree(const LinkedBinaryTree& t); // copy constructor
  Node* copyPreOrder(const Node* root); // copy binary tree recursively
  LinkedBinaryTree& operator=(const LinkedBinaryTree& t);
  int size() const;                // number of nodes
  bool empty() const;              // is tree empty?
  Position root() const;           // get the root
  PositionList positions() const;  // list of nodes
  void addRoot();                  // add root to empty tree
  void expandExternal(
      const Position &p);  // expand external node (create left, right children)
  Position removeAboveExternal(const Position &p);  // remove p and parent

  void printExpression(); // print expresssion helper
  void printExpression(Node* leaf); // print expresssion recursive
  double evaluateExpression(double a, double b); // evaluate expresssion helper
  double evaluateExpression(double a, double b, Node* leaf); // evaluate expresssion recursive
  double getScore(); // returns score
  void setScore(double s);
  // housekeeping functions omitted. . .
 protected:                                        // local utilities
  void preorder(Node *v, PositionList &pl) const;  // preorder utility
 private:
  Node *root_p;  // pointer to the root
  int n;         // number of nodes
  string input = "";
  double score = 0;

  friend LinkedBinaryTree createExpressionTree(string postfix);
};

LinkedBinaryTree::LinkedBinaryTree()  // constructor
    : root_p(NULL), n(0) {}

LinkedBinaryTree::~LinkedBinaryTree() {  // destructor
  if (root_p != NULL)  // self destructs only if root is not NULL, smartly defends against seg faults
  {
    PositionList pl = positions();
    for (auto &p : pl) {
      delete p.v;
    }
  }
}

// copy constructor 
LinkedBinaryTree::LinkedBinaryTree(const LinkedBinaryTree& t) {
  root_p = copyPreOrder(t.root_p);
  score = t.score;
}

// used by copy constructor to recursively copy the tree
LinkedBinaryTree::Node* LinkedBinaryTree::copyPreOrder(const Node* root) {
  if (root == NULL) return NULL;
  Node* nn = new Node;
  nn->elt = root->elt;

  nn->left = copyPreOrder(root->left);
  if (nn->left != NULL) nn->left->par = nn;

  nn->right = copyPreOrder(root->right);
  if (nn->right != NULL) nn->right->par = nn;

  return nn;
}

// overloads assignment operator, somehow prevents the destructor from breaking
LinkedBinaryTree &LinkedBinaryTree::operator=(const LinkedBinaryTree &t) {
  if (this != &t) {
    // DEBUG: added the next 4 lines to delete the old binary tree which is being copied
    if (root_p != NULL) {
      PositionList pl = positions();
      for (auto &p : pl) delete p.v;
    }
    root_p = copyPreOrder(t.root_p);
    score = t.score;
  }
  return *this;
}

int LinkedBinaryTree::size() const  // number of nodes
{
  return n;
}
bool LinkedBinaryTree::empty() const  // is tree empty?
{
  return size() == 0;
}

LinkedBinaryTree::Position
LinkedBinaryTree::root() const  // get the root
{
  return Position(root_p);
}

void LinkedBinaryTree::addRoot()  // add root to empty tree
{
  root_p = new Node;
  n = 1;
}

void LinkedBinaryTree::expandExternal(const Position &p) {
  Node *v = p.v;        // p’s node
  v->left = new Node;   // add a new left child
  v->left->par = v;     // v is its parent
  v->right = new Node;  // and a new right child
  v->right->par = v;    // v is its parent
  n += 2;               // two more nodes
}

// remove p and parent
LinkedBinaryTree::Position
LinkedBinaryTree::removeAboveExternal(const Position &p) {
  Node *w = p.v;
  Node *v = w->par;  // get p’s node and parent
  Node *sib = (w == v->left ? v->right : v->left);
  if (v == root_p) {  // child of root?
    root_p = sib;     // . . .make sibling root
    sib->par = NULL;
  } else {
    Node *gpar = v->par;  // w’s grandparent
    if (v == gpar->left)
      gpar->left = sib;  // replace parent by sib
    else
      gpar->right = sib;
    sib->par = gpar;
  }
  delete w;
  delete v;  // delete removed nodes
  n -= 2;    // two fewer nodes
  return Position(sib);
}

LinkedBinaryTree::PositionList
LinkedBinaryTree::positions() const {
  PositionList pl;
  preorder(root_p, pl);     // preorder traversal
  return PositionList(pl);  // return resulting list
}

// preorder traversal
void LinkedBinaryTree::preorder(Node *v, PositionList &pl) const {
  pl.push_back(Position(v));  // add this node
  if (v->left != NULL)        // traverse left subtree
    preorder(v->left, pl);
  if (v->right != NULL)  // traverse right subtree
    preorder(v->right, pl);
}

// helper function for evaluate expression since we need more parameters to do this recursively
double LinkedBinaryTree::evaluateExpression(double a, double b) {
  return evaluateExpression(a, b, root_p);
}

// evalutes the expression in a binary tree recursively
double LinkedBinaryTree::evaluateExpression(double a, double b, Node* leaf) {
  Position current = Position(leaf); // uses a position object to determine if node is external
  if (current.isExternal()) // only constants and a, b variables will be external
  {
    if (leaf->elt == "a") // returns a input if the variable a is in the expression
    {
      return a;
    }
    else if (leaf->elt == "b") // returns b input if the variable b is in the expression
    {
      return b;
    }
    else
    {
      return stod(leaf->elt); // returns value as a double if it is a constant number
    }
  }
  else
  {
    if (leaf->elt == "abs") // since abs value only has one child
    {
      return abs(evaluateExpression(a, b, leaf->left)); // returns the absolute value of the left child node/tree
    }
    else
    {
      if (leaf->elt == "+") // if an addition operator is detected
      {
        return evaluateExpression(a, b, leaf->left) + evaluateExpression(a, b, leaf->right); // adds both child nodes
      }
      else if (leaf->elt == "-") // if a subtraction operator is detected
      {
        return evaluateExpression(a, b, leaf->left) - evaluateExpression(a, b, leaf->right); // subtracts both child nodes
      }
      else if (leaf->elt == "*") // if a multiplication operator is detected
      {
        return evaluateExpression(a, b, leaf->left) * evaluateExpression(a, b, leaf->right); // multiplies both child nodes
      }
      else if (leaf->elt == "/") // if a division operator is detected
      {
        double denominator = evaluateExpression(a, b, leaf->right); // calculates the denominator (right child node)
        if (denominator == 0)
        {
          throw runtime_error("Please do not divide by zero..."); // will only throw this error if denominator is determined to be 0
        }
        else
        {
          return evaluateExpression(a, b, leaf->left) / denominator; // divides both child nodes
        }
      }
      else if (leaf->elt == ">") // if a greater than operator is detected
      {
        if (evaluateExpression(a, b, leaf->left) > evaluateExpression(a, b, leaf->right)) // compares left and right child
        {
          return 1; // returns 1 if left child is greater than the right
        }
        else
        {
          return -1; // returns -1 otherwise
        }
      }
      else
      { // will throw this error only if an unexpected operator is inputted
        throw runtime_error("Your operator input of " + leaf->elt + " is not valid...");
      }
    }
  }
}

// helper function to print expression recursively
void LinkedBinaryTree::printExpression() {
  printExpression(root_p);
}

// prints the expression in the binary tree recursively
void LinkedBinaryTree::printExpression(Node* leaf) {
  Position current = Position(leaf); // uses a position object to determine if node is external
  if (current.isExternal())
  { // if value is a constant or an a, b variable without children
    cout << leaf->elt;
  }
  else if (leaf->elt == "abs")
  { // if value is absolute value
    cout << leaf->elt;
    cout << "("; // cleverly prints absolute value before the brackets
    printExpression(leaf->left);
    cout << ")";
  }
  else { // value must be another operator or has kids
    cout << "(";
    printExpression(leaf->left);
    cout << " " << leaf->elt << " ";
    printExpression(leaf->right);
    cout << ")";
  }
  // if (root_p == leaf) { /* UNCOMMENT TO SEPARATE PRINTED EXPRESSIONS */
  //   cout << "\n";
  // }
}

// returns the score of the binary tree expression as a double
double LinkedBinaryTree::getScore() {
  return score; // score is stored as a private value of the binary tree object
}

// sets the score to whatever the user has inputted
void LinkedBinaryTree::setScore(double s) {
  score = s;
}

// overloads the less than comparison operator, used for sorting
bool operator<(LinkedBinaryTree &treeOne, LinkedBinaryTree &treeTwo)
{
  return (treeOne.getScore() < treeTwo.getScore()); // compares the scores of two trees to sort in ascending order
}

// helper function for the constructor, basically uses the constructor and then creates the necessary nodes for the tree
LinkedBinaryTree createExpressionTree(string postfix) {
  LinkedBinaryTree tree;
  stack<LinkedBinaryTree::Node*> nodes; // uses the stack to store values as nodes and branches are created
  // tree.addRoot(); // DEBUG: No longer using the addRoot function as it causes memory leaks
  tree.input = postfix; // saves the postfix expression as a variable of the object to be used later (necessary for function)

  int index = 0;
  string exp; // these variable help iterate through the string
  while (tree.input[index] != '\0') // repeats until NULL is reached (end of string)
  {
    exp = ""; // resets exp variable each iteration
    while (isspace(tree.input[index]) == false && tree.input[index] != '\0') // repeats until the end of the operator or operand
    {
      exp += tree.input[index]; // records operator or operand to be used later
      index++;
    }

    if (exp != "abs" && exp != "-" && exp != "*" && exp != "/" && exp != "+" && exp != ">") // checks if the extracted string is not an accepted operator
    { // if value is a number
      LinkedBinaryTree::Node* number = new LinkedBinaryTree::Node;
      number->elt = exp;
      nodes.push(number); // saves number value to a node and into a stack to be added to the tree later
      tree.n += 1; // increments the size of the tree (not used in my extension of the class but should still be recorded)
    }
    else if (exp == "abs")
    { // if extracted string is the absolute value operator
      LinkedBinaryTree::Node *absValue = new LinkedBinaryTree::Node;
      absValue->elt = exp; // creates a node for the absolute value operator
      absValue->left = nodes.top(); // pops the most recent node in the stack so the abs value node can adopt it
      nodes.pop();
      absValue->right = NULL; // no second child for the abs value, kinda sad cause then left node is a single child
      absValue->left->par = absValue;
      nodes.push(absValue); // pushes tree back to stack
      tree.n += 1; // size
    }
    else
    { // if extracted string is anything else (an accepted operator)
      LinkedBinaryTree::Node *operation = new LinkedBinaryTree::Node;
      operation->elt = exp;
      operation->right = nodes.top(); // creates a node for the operator and sets two most recent nodes to be its children
      nodes.pop();
      operation->left = nodes.top();
      nodes.pop();
      operation->right->par = operation; // sets parents for recents nodes
      operation->left->par = operation;
      nodes.push(operation); // pushes tree back to stack
      tree.n += 1; // size
    }
    if (tree.input[index] != '\0') index++; // only increment if NULL is not reached, prevents seg faults
  }
  tree.root_p = nodes.top(); // top node in stack shall be the root
  nodes.pop();
  // tree.n -= 1; // Not using new
  return tree; // finished tree is returned. Wow!
}

int main() {
  // Read postfix expressions into vector
  vector<LinkedBinaryTree> trees;
  ifstream exp_file("expressions.txt");
  string line;
  while (getline(exp_file, line)) {
    trees.push_back(createExpressionTree(line));
  }

  // Read input data into 2D vector
  vector<vector<double>> inputs;
  ifstream input_file("input.txt");
  while (getline(input_file, line)) {
    vector<double> ab_input;
    stringstream ss(line);
    string str;
    while (getline(ss, str, ' ')) {
      ab_input.push_back(stod(str));
    }
    inputs.push_back(ab_input);
  }

  // Evaluate expressions on input data
  for (auto &t : trees) {
    double sum = 0;
    for (auto &i : inputs) {
      sum += t.evaluateExpression(i[0], i[1]);
    }
    t.setScore(sum / inputs.size());
  }

  // Sort trees by their score
  sort(trees.begin(), trees.end());
   for (auto &t : trees)
   {
     cout << "Exp ";
     t.printExpression();
     cout << " Score " << t.getScore() << endl;
   }
  return EXIT_SUCCESS;
}