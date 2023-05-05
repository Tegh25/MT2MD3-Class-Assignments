#include <cstdlib>
#include <iostream>

int main() {
    
    // initializing integer and pointer according to question 1
    int x = 21;
    int* A = &x;

    // expression to obtain a value that is twice the value of A's referent
    int y = (*A)*2;

    //printf("%d\n", y);
    std::cout << y;

    //return 0;
    return EXIT_SUCCESS;
}