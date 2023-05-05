#include <cstdlib>
#include <iostream>

void f(int x)
{ std::cout << ++x; }

void g(int& x)
{ std::cout << ++x; }

int main() {
    
    int x = 2;

    f(x);

    std::cout << x;

    g(x);

    std::cout << x;

    //return 0;
    return EXIT_SUCCESS;
}