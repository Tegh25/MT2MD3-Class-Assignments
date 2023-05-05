#include <cstdlib>
#include <iostream>
using namespace std;

int main() {

    // creates array of 10 pointer types
    double* dp[10];
    // each index of the array will point to a double value of 0
    for (int i = 0; i < 10; i++) dp[i] = new double(0.0);
    
    for (int i = 0; i < 10; i++) cout << *dp[i] << endl;

    // delete the array of pointers as it's no longer needed
    delete [] dp;

    return EXIT_SUCCESS;
}