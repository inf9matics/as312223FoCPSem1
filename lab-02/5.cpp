#include <iostream>
#include <cmath>

int main(){
    int a, b, c;
    std::cout << "Quadratic equation solver" << std::endl;
    std::cout << "Input a: ";
    std::cin >> a;
    std::cout << "Input b: ";
    std::cin >> b;
    std::cout << "Input c: ";
    std::cin >> c;

    float delta = pow(b, 2) - (4 * (a * c));

    float x1, x2;
    if(delta > 0){
        x1 = ((-1) * b + sqrt(delta))/(2 * a);
        x2 = ((-1) * b - sqrt(delta))/(2 * a);
    }
    else if(delta < 0){
        std::cout << "There are no solutions" << std::endl;

        return 0;
    }
    else{
        x1 = ((-1) * b + sqrt(delta))/(2 * a);
        x2 = x1;
    }

    if(x1==x2){
        std::cout << "There is 1 double solution:" << std::endl << "x=" << x1 << std::endl;
    }
    else{
        std::cout << "There are 2 solutions:" << std::endl << "x1=" << x1 << std::endl << "x2=" << x2 << std::endl;
    }

    return 0;
}