#include <cstdlib>
#include <iostream>
using namespace std;

void print(int arr[][3]) { // prints entire array, used for testing
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      cout << arr[i][j] << "\n";
    }
  }
}

// outputMin function takes in array that simulates a linked list and outputs the smallest value in the list greater than x
int outputMin(int arr[][3]) {
    int elements = arr[0][0]; // retrieves the important values from the first row of the array
    int index = arr[0][1];
    int x = arr[0][2];

    for (int i = 0; i < elements; i++) { // iterates through the list
        if (arr[index][0] >= x) { // since list is sorted, we can return the first value greater than x
            return arr[index][0];
        } else {
            index = arr[index][1]; // go to next value in list of not greater than x
        }
    }
    return -1; // if value >= x not found
}

int main() {
  int elements, index, x;
  cout << "Enter the elements, index, and x values in order as integers and separated by a space: ";
  cin >> elements >> index >> x;

  int input[elements + 1][3];
  input[0][0] = elements;
  input[0][1] = index;
  input[0][2] = x;

  int value, next;
  for (int i = 1; i < elements + 1; i++) {
    cout << "Enter the value and index for next pointer respectively for node " << i << ": ";
    cin >> value >> next; input[i][0] = value; input[i][1] = next;
    input[i][2] = 0;
  }

  // uncomment line below and comment above to skip the user input!
  // int input[6][3] = {{5, 3, 81}, {97, -1}, {58, 5}, {16, 2}, {81, 1}, {79, 4}};

  cout << outputMin(input) << "\n";

  return EXIT_SUCCESS;
}