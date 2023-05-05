#include <cstdlib>
#include <iostream>

// function gcd takes in two integers n, m with n > m
// gcd returns an integer that represents the greatest common divisor of the inputs
int gcd(int n, int m) {
    // calculating the remainder using the modulus operator by the Chinese Remainder Theorem
    int j = n % m;
    // if j = 0, it means m can no longer go into n, this means m is the gcd
    if (j == 0) {
        return m;
    } else {
        // function repeats recursively if gcd is not found, m becomes n and j becomes m
        gcd(m, j);
    }
} // end of gcd function

int main() {

    std::cout << gcd(80844,25320) << std::endl;

    return EXIT_SUCCESS;
}