#include <cstdlib>
#include <iostream>

// numDivisions function takes positive double as input and outputs integer
// output shows how many times x can be halved before it is less than 2 
int numDivisions(double x) {
    int divisions;
    // loop iterates if and until x becomes less than 2
    while (x >= 2) {
        // halves x and increments divisions counter each iteration
        x = x/2;
        divisions++;
    }
    // returns output as int
    return divisions;
} // end of num Divisions function

int main() {

    std::cout << numDivisions(1) << std::endl;
    std::cout << numDivisions(2) << std::endl;
    std::cout << numDivisions(3) << std::endl;
    std::cout << numDivisions(4) << std::endl;
    std::cout << numDivisions(5) << std::endl;
    std::cout << numDivisions(6) << std::endl;
    std::cout << numDivisions(7) << std::endl;
    std::cout << numDivisions(8) << std::endl;

    return EXIT_SUCCESS;
}