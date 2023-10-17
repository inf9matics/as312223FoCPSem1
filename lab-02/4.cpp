#include <iostream>
#include <cmath>

int main(){
    int a, b, c;
    std::cout << "a + bx = c equation solver" << std::endl;
    std::cout << "Input a: ";
    std::cin >> a;
    std::cout << "Input b: ";
    std::cin >> b;
    std::cout << "Input c: ";
    std::cin >> c;

    float x = (c - b)/a;

    std::cout << "Your solution is:" << std::endl << "x=" << x << std::endl;

    return 0;
}