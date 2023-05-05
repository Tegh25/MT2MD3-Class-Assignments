#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// stack implementation using c++ vectors
class Stack {
 public:
  Stack();
  ~Stack();
  void push(double num);
  double pop();
  double front();
  int size();
  bool empty();

 private: // vector stored as private variable
  vector<double> newStack;
};

Stack::Stack() { // constructor
  vector<double> newStack;
}

Stack::~Stack() { // destructor
  // delete newStack;
}

void Stack::push(double num) { // pushes double value into stack
  newStack.insert(newStack.begin(), num);
}

double Stack::pop() { // pops front value out of stack
  if (!empty()) {
    double elem = front();
    newStack.erase(newStack.begin());
    return elem;
  } else { // throws error if stack is empty before popping
    throw runtime_error("Error: malformed expression\n");
  }
}

double Stack::front() { // returns front of stack without removing the value
  if (!empty()) {
    return newStack.front();
  } else { // throws error if stack is empty before calling front
    throw runtime_error("Error: malformed expression\n");
  }
}

int Stack::size() { // returns size of stack as integer
  return newStack.size();
}

bool Stack::empty() { // returns boolean true if stack is empty, false if not
  if (size() > 0) {
    return false;
  }
  return true;
}

// RPNEvaluator class stores and evaluates polish notation equations as strings
class RPNEvaluator {
  public:
  RPNEvaluator(string e);
  ~RPNEvaluator();
  double Evaluate();
  double operation(double x, double y, char op);
  int size();

  private: // string stored as variable
  string rpnString;
};

RPNEvaluator::RPNEvaluator(string e) { // constructor
  rpnString = e;
}

RPNEvaluator::~RPNEvaluator() { // destructor
  // delete rpnString;
}

double RPNEvaluator::Evaluate() { // evaluate method evaluates the string and prints/returns as double
  Stack Nums;
  for (int i = 0; i < size(); i+=2) { // iterates through string for each char, skipping the spaces
    try { // checks if character at index is operator
      if (rpnString[i] == '+' || rpnString[i] == '-' || rpnString[i] == '*' || rpnString[i] == '/') {
        double y = Nums.pop();
        double x = Nums.pop(); // pops values from stack and calculates operation
        Nums.push(operation(x, y, (char)rpnString[i]));
      }
      else if (0 <= stod(&rpnString[i]) <= 9) { // checks if character at index is an acceptable double
        Nums.push(stod(&rpnString[i])); // casts and pushes double to stack
      }
    }
    catch (invalid_argument &e) { // throws invalid argument if character is not of an accepted type
      throw invalid_argument("Error: malformed expression\n");
    }
  } // prints and returns solution to equation
  cout << Nums.front() << "\n";
  return Nums.front();
}

// given two values, performs the operation specified in char input
double RPNEvaluator::operation(double x, double y, char op) {
  if (op == '+') { // addition
    return x + y;
  } 
  else if (op == '-') { // subtraction
    return x - y;
  }
  else if (op == '*') { // multiplacation
    return x * y;
  }
  else {
    if (y != 0) { // division only if divisor is not 0
      return x / y;
    }
    else { // throws error if trying to divide by zero
      throw runtime_error("Error: malformed expression\n");
    }
  }
}

// returns size of string as integer
int RPNEvaluator::size() {
  return rpnString.size();
}

/* TEST CASES */

// 5 2 + 8 3 - * 4 /
// 7 5 * 4 /
// 35 4 /
// 8.75

// 6 3 - 1 3 + * 1 6 - 3 * /
// -0.8

// given main function
int main() {
  std::string rpn_exp;
  std::cout << "Please enter an expression in RPN format: ";
  std::getline(std::cin, rpn_exp);
  RPNEvaluator rpn(rpn_exp);
  rpn.Evaluate();
  return EXIT_SUCCESS;
}