#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

/*
Author: Teghveer Ateliey
Date created: Feb 6, 2023
Last modified: Feb 6, 2023
Purpose: To find both the minimum and maximum values in a c++ vector of int values without using any loops
*/

// tail recursive function maxMin takes in vector as initial input and outputs the max and minimium values in that vector 
void maxMin(vector<int> v, int min = INT_MAX, int max = INT_MIN, int n = 0) {
    if (n >= (int)v.size()) { // base case prints and ends recursion once we reach the end of the vector
        cout << "Min " << min << " Max " << max << endl; 
    }
    else if (max < v.at(n)) { // updates max if value it index is greater and calls function again for next index 
        max = v.at(n);
        maxMin(v, min, max, n + 1);
    }
    else if (min > v.at(n)) { // updates min if value at index is lesser and calls function again for next index 
        min = v.at(n);
        maxMin(v, min, max, n + 1);
    }
    else { // calls function again for next index even if max and min were not updated
        maxMin(v, min, max, n + 1);
    }
} // end of maxMin function

// start of main function
int main() {
    vector<int> nums = {1, -2, 0, 6, 66, -7};
    //vector<int> nums = {1, -279, 100, 678, 66, -7};

    maxMin(nums); // prints values in function instead of in main

    return EXIT_SUCCESS;
} // end of main function