#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

// prints the vector, not part of the answer to this question just mainly used for testing
void print(std::vector<int> const &a) {
  std::cout << "The vector elements are : ";
  for (int i = 0; i < a.size(); i++) std::cout << a.at(i) << ' ';
}

// recursive function to reorder vector into displaying even numbers before odd
void evenOdd(vector<int> &v, int i = 0, int counter = 0) {
  if (counter == v.size()) { // base case tracks if we've recursively traveled through whole vector
    print(v);
  } else {
    if (v.at(i) % 2 == 0) {
      i++;
      counter++;
    } else {
      v.push_back(v.at(i));
      v.erase(v.begin() + i);
      counter++;
    }
    evenOdd(v, i, counter);
  }
}

int main() {
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  print(nums);
  cout << "\n";

  evenOdd(nums);
  cout << "\n";

  return EXIT_SUCCESS;
}