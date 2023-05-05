#include <math.h>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stack>
#include <vector>
#include "cartCentering.h"

using namespace std;

// return a double unifomrly sampled in (0,1)
double randDouble(mt19937& rng) {
  return std::uniform_real_distribution<>{0, 1}(rng);
}
// return uniformly sampled 0 or 1
bool randChoice(mt19937& rng) {
  return std::uniform_int_distribution<>{0, 1}(rng);
}
// return a random integer uniformly sampled in (min, max)
int randInt(mt19937& rng, const int& min, const int& max) {
  return std::uniform_int_distribution<>{min, max}(rng);
}

// return true is op is a suported operation, otherwise return false
bool isOp(string op) {
  if (op == "+")
    return true;
  else if (op == "-")
    return true;
  else if (op == "*")
    return true;
  else if (op == "/")
    return true;
  else if (op == ">")
    return true;
  else if (op == "abs")
    return true;
  else
    return false;
}

int arity(string op) {
  if (op == "abs")
    return 1;
  else
    return 2;
}

typedef string Elem;

class LinkedBinaryTree {
 public:
  struct Node {
    Elem elt;
    string name;
    Node* par;
    Node* left;
    Node* right;
    Node() : elt(), par(NULL), name(""), left(NULL), right(NULL) {}
    int depth() {
      if (par == NULL) return 0;
      return par->depth() + 1;
    }
  };

  class Position {
   private:
    Node* v;

   public:
    Position(Node* _v = NULL) : v(_v) {}
    Elem& operator*() { return v->elt; }
    Position left() const { return Position(v->left); }
    void setLeft(Node* n) { v->left = n; }
    Position right() const { return Position(v->right); }
    void setRight(Node* n) { v->right = n; }
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
  typedef vector<Position> PositionList;

 public:
  LinkedBinaryTree() : _root(NULL), score(0), steps(0), generation(0) {}

  // copy constructor
  LinkedBinaryTree(const LinkedBinaryTree& t) {
    _root = copyPreOrder(t.root());
    score = t.getScore();
    steps = t.getSteps();
    generation = t.getGeneration();
  }

  // copy assignment operator
  LinkedBinaryTree& operator=(const LinkedBinaryTree& t) {
    if (this != &t) {
      // If tree already contains data, delete it
      if (_root != NULL) {
        PositionList pl = positions();
        for (auto& p : pl) delete p.v;
      }
      _root = copyPreOrder(t.root());
      score = t.getScore();
      steps = t.getSteps();
      generation = t.getGeneration();
    }
    return *this;
  }

  // destructor
  ~LinkedBinaryTree() {
    if (_root != NULL) {
      PositionList pl = positions();
      for (auto& p : pl) delete p.v;
    }
  }

  int size() const { return size(_root); }
  int size(Node* root) const;
  int depth() const;
  bool empty() const { return size() == 0; };
  Node* root() const { return _root; }
  PositionList positions() const;
  void addRoot() { _root = new Node; }
  void addRoot(Elem e) {
    _root = new Node;
    _root->elt = e;
  }
  void nameRoot(string name) { _root->name = name; }
  void addLeftChild(const Position& p, const Node* n);
  void addLeftChild(const Position& p);
  void addRightChild(const Position& p, const Node* n);
  void addRightChild(const Position& p);
  void printExpression() { printExpression(_root); }
  void printExpression(Node* v);
  double evaluateExpression(double a, double b) {
    return evaluateExpression(Position(_root), a, b);
  };
  double evaluateExpression(const Position& p, double a, double b);
  long getGeneration() const { return generation; }
  void setGeneration(int g) { generation = g; }
  double getScore() const { return score; }
  void setScore(double s) { score = s; }
  double getSteps() const { return steps; }
  void setSteps(double s) { steps = s; }
  void randomExpressionTree(Node* p, const int& maxDepth, mt19937& rng);
  void randomExpressionTree(const int& maxDepth, mt19937& rng) {
    randomExpressionTree(_root, maxDepth, rng);
  }
  void deleteSubtreeMutator(mt19937& rng);
  void deleteSubtreeRecursive(Position node); // my implemented
  void addSubtreeMutator(mt19937& rng, const int maxDepth);

 protected:                                        // local utilities
  void preorder(Node* v, PositionList& pl) const;  // preorder utility
  Node* copyPreOrder(const Node* root);
  double score;     // mean reward over 20 episodes
  double steps;     // mean steps-per-episode over 20 episodes
  long generation;  // which generation was tree "born"
 private:
  Node* _root;  // pointer to the root
};

// add the tree rooted at node child as this tree's left child
void LinkedBinaryTree::addLeftChild(const Position& p, const Node* child) {
  Node* v = p.v;
  v->left = copyPreOrder(child);  // deep copy child
  v->left->par = v;
}

// add the tree rooted at node child as this tree's right child
void LinkedBinaryTree::addRightChild(const Position& p, const Node* child) {
  Node* v = p.v;
  v->right = copyPreOrder(child);  // deep copy child
  v->right->par = v;
}

void LinkedBinaryTree::addLeftChild(const Position& p) {
  Node* v = p.v;
  v->left = new Node;
  v->left->par = v;
}

void LinkedBinaryTree::addRightChild(const Position& p) {
  Node* v = p.v;
  v->right = new Node;
  v->right->par = v;
}

// return a list of all nodes
LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const {
  PositionList pl;
  preorder(_root, pl);
  return PositionList(pl);
}

void LinkedBinaryTree::preorder(Node* v, PositionList& pl) const {
  pl.push_back(Position(v));
  if (v->left != NULL) preorder(v->left, pl);
  if (v->right != NULL) preorder(v->right, pl);
}

int LinkedBinaryTree::size(Node* v) const {
  int lsize = 0;
  int rsize = 0;
  if (v->left != NULL) lsize = size(v->left);
  if (v->right != NULL) rsize = size(v->right);
  return 1 + lsize + rsize;
}

int LinkedBinaryTree::depth() const {
  PositionList pl = positions();
  int depth = 0;
  for (auto& p : pl) depth = std::max(depth, p.v->depth());
  return depth;
}

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

void LinkedBinaryTree::printExpression(Node* v) {
  if (v != NULL) {  // base case
    if (isOp(v->elt) && arity(v->elt) > 1) {
      cout << "(";
      printExpression(v->left);
      cout << " " << v->elt << " ";
      printExpression(v->right);
      cout << ")";
    } else if (isOp(v->elt)) {
      cout << v->elt;
      cout << "(";
      printExpression(v->left);
      cout << ")";
    } else {
      cout << (v->name != "" ? v->name : v->elt);
    }
  }
}

double evalOp(string op, double x, double y = 0) {
  double result;
  if (op == "+")
    result = x + y;
  else if (op == "-")
    result = x - y;
  else if (op == "*")
    result = x * y;
  else if (op == "/") {
    result = x / y;
  } else if (op == ">") {
    result = x > y ? 1 : -1;
  } else if (op == "abs") {
    result = abs(x);
  } else
    result = 0;
  return isnan(result) || !isfinite(result) ? 0 : result;
}

double LinkedBinaryTree::evaluateExpression(const Position& p, double a,
                                            double b) {
  if (!p.isExternal()) {
    auto x = evaluateExpression(p.left(), a, b);
    if (arity(p.v->elt) > 1) {
      auto y = evaluateExpression(p.right(), a, b);
      return evalOp(p.v->elt, x, y);
    } else {
      return evalOp(p.v->elt, x);
    }
  } else {
    if (p.v->elt == "a")
      return a;
    else if (p.v->elt == "b")
      return b;
    else
      return stod(p.v->elt);
  }
}

// chooses a subtree to delete
void LinkedBinaryTree::deleteSubtreeMutator(mt19937& rng) {
  // my implementation here
  PositionList pl = positions();
  int index = randInt(rng, 1, pl.size() - 1); // chooses a random index
  if (!pl[pl.size() - index].isExternal() && !pl[pl.size() - index].isRoot()) {
    deleteSubtreeRecursive(pl[pl.size() - index]); // deletes subtree if index is valid
  }
}

// deletes chosen subtree recursively
void LinkedBinaryTree::deleteSubtreeRecursive(Position node) {
  if (node.left().v != NULL) { // deletes left child if not NULL
    deleteSubtreeRecursive(node.left());
  }
  if (node.right().v != NULL) { // deletes right child if not NULL
    deleteSubtreeRecursive(node.right());
  }
  delete node.v; // deletes node
}

// adds a subtree at external nodes
void LinkedBinaryTree::addSubtreeMutator(mt19937& rng, const int maxDepth) {
  // my implementation here
  PositionList pl = positions();
  int index = randInt(rng, 1, pl.size() - 1); // choose a random integer in the range of the PositionsList
  if (pl[pl.size() - index].isExternal()) { // adds subtree only if random index is external
    randomExpressionTree(pl[pl.size() - index].v, maxDepth, rng);
  }
  else { // if random index is invalid, iterate through tree until a valid index is found
    for (int i = 1; i < pl.size(); i++) {
      if (pl[pl.size() - i].isExternal()) { // 4 is good
        randomExpressionTree(pl[pl.size() - i].v, maxDepth, rng);
      }
    }
  }
}

bool operator<(const LinkedBinaryTree& x, const LinkedBinaryTree& y) {
  return x.getScore() < y.getScore();
}

LinkedBinaryTree createExpressionTree(string postfix) {
  stack<LinkedBinaryTree> tree_stack;
  stringstream ss(postfix);
  // Split each line into words
  string token;
  while (getline(ss, token, ' ')) {
    LinkedBinaryTree t;
    if (!isOp(token)) {
      t.addRoot(token);
      tree_stack.push(t);
    } else {
      t.addRoot(token);
      if (arity(token) > 1) {
        LinkedBinaryTree r = tree_stack.top();
        tree_stack.pop();
        t.addRightChild(t.root(), r.root());
      }
      LinkedBinaryTree l = tree_stack.top();
      tree_stack.pop();
      t.addLeftChild(t.root(), l.root());
      tree_stack.push(t);
    }
  }
  return tree_stack.top();
}

// return a random operator
string randOp(mt19937& rng) {
  const int NUM_OP = 6;
  int op = randInt(rng, 0, NUM_OP - 1);
  if (op == 0)
    return "+";
  else if (op == 1)
    return "-";
  else if (op == 2)
    return "*";
  else if (op == 3)
    return "/";
  else if (op == 4)
    return ">";
  else
    return "abs";
}

// create a random expression tree rooted at node p
void LinkedBinaryTree::randomExpressionTree(Node* p, const int& maxDepth,
                                            mt19937& rng) {
  // Two conditions in which we want to create a new operator node:
  // 1. p is the tree root
  if (p->par == NULL ||
      // 2. Depth of p is less than maxDepth and
      // our random choice to select operator or operand is true
      (p->depth() < maxDepth && randChoice(rng))) {
    string op = randOp(rng);
    p->elt = op;
    addLeftChild(Position(p));
    randomExpressionTree(p->left, maxDepth, rng);
    if (arity(op) > 1) {
      addRightChild(Position(p));
      randomExpressionTree(p->right, maxDepth, rng);
    }
  } else {  // otherwise create an operand node
    p->elt = randChoice(rng) ? "a" : "b";
  }
}

// evaluate tree t in the cart centering task
void evaluate(mt19937& rng, LinkedBinaryTree& t, const int& num_episode,
              bool animate) {
  cartCentering env;
  double mean_score = 0.0;
  double mean_steps = 0.0;
  for (int i = 0; i < num_episode; i++) {
    double episode_score = 0.0;
    int episode_steps = 0;
    env.reset(rng);
    while (!env.terminal()) {
      int action = t.evaluateExpression(env.getCartXPos(), env.getCartXVel());
      episode_score += env.update(action, animate);
      episode_steps++;
    }
    mean_score += episode_score;
    mean_steps += episode_steps;
  }
  t.setScore(mean_score / num_episode);
  t.setSteps(mean_steps / num_episode);
}

class LexLessThan {  // a lexLessThan comparator
 public: // overloads () operater to perform comparison 
  bool operator()(const LinkedBinaryTree& a, const LinkedBinaryTree& b) const {
    if (abs(a.getScore() - b.getScore()) < 0.006) { // worse fitness/size should be true
      return a.size() > b.size(); // returns this if a and b has similar scores
    }
    else {
      return a < b;
    }
  }
};

int main() {
  mt19937 rng(42); // 42 default
  // Experiment parameters
  const int NUM_TREE = 10; // 10 to have generations calculated quickly
  const int MAX_DEPTH_INITIAL = 20; // 20 to have simpler starting trees which generally have better fitness
  const int MAX_DEPTH = 5; // 5 to have simpler with a decent amount of mutation
  const int NUM_EPISODE = 5; // 5 to have generations calculated quickly
  const int MAX_GENERATIONS = 2500; // 2500 is enough generations to be confident we have the best tree possible

  // Create a "population" of random expression trees
  vector<LinkedBinaryTree> trees;
  for (int i = 0; i < NUM_TREE; i++) {
    LinkedBinaryTree t;
    t.addRoot();
    t.randomExpressionTree(MAX_DEPTH_INITIAL, rng);
    trees.push_back(t);
  }

  // Genetic Algorithm loop
  LinkedBinaryTree best_tree;
  std::cout << "generation,score,steps,size,depth" << std::endl;
  for (int g = 1; g <= MAX_GENERATIONS; g++) {

    // Fitness evaluation
    for (auto& t : trees) {
      if (t.getGeneration() < g - 1) continue;  // skip if not new
      evaluate(rng, t, NUM_EPISODE, false);
    }

    // sort trees (worst->best)
    // sort using overloaded "<" op
    // std::sort(trees.begin(), trees.end());
    // sort using comparaor class  
    std::sort(trees.begin(), trees.end(), LexLessThan());

    // erase worst 50% of trees (first half of vector)
    trees.erase(trees.begin(), trees.begin() + NUM_TREE / 2);

    // Print stats for best tree
    best_tree = trees[trees.size() - 1];
    std::cout << g << ",";
    std::cout << best_tree.getScore() << ",";
    std::cout << best_tree.getSteps() << ",";
    std::cout << best_tree.size() << ",";
    std::cout << best_tree.depth() << std::endl;

    // Selection and mutation
    while (trees.size() < NUM_TREE) {
      // Selected random "parent" tree from survivors
      LinkedBinaryTree parent = trees[randInt(rng, 0, (NUM_TREE / 2) - 1)];
      
      // Create child tree with copy constructor
      LinkedBinaryTree child(parent);
      child.setGeneration(g);
      
      // Mutation
      // Delete a randomly selected part of the child's tree
      // child.deleteSubtreeMutator(rng);
      // Add a random subtree to the child
      child.addSubtreeMutator(rng, MAX_DEPTH);
      
      trees.push_back(child);
    }
  }

  // // Evaluate best with animation
  // const int num_episode = 3;
  // evaluate(rng, best_tree, num_episode, true);

  // Print best tree info
  std::cout << std::endl << "Best tree:" << std::endl;
  best_tree.printExpression();
  std::cout << endl;
  std::cout << "Generation: " << best_tree.getGeneration() << endl;
  std::cout << "Size: " << best_tree.size() << std::endl;
  std::cout << "Depth: " << best_tree.depth() << std::endl;
  std::cout << "Fitness: " << best_tree.getScore() << std::endl << std::endl;
}