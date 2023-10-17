#include <iostream>
#include <cmath>

int main(){
    int a1, b1, c1, a2, b2, c2;
    std::cout << "Two linear equations solver" << std::endl;
    std::cout << "Input a1: ";
    std::cin >> a1;
    std::cout << "Input b1: ";
    std::cin >> b1;
    std::cout << "Input c1: ";
    std::cin >> c1;

    std::cout << "Input a2: ";
    std::cin >> a2;
    std::cout << "Input b2: ";
    std::cin >> b2;
    std::cout << "Input c2: ";
    std::cin >> c2;

    //y = (c1 - a1x)/b1 = c1/b1 - a1x/b1 = n1 + m1x
    //m1 = -a1/b1
    //n1 = c1/b1
    //m1x + n1 = m2x + n2
    //m1x + n1 - m2x - n2 = 0
    //m1x - m2x = n2 - n1
    //

    float m1 = ((-1) * a1) / b1;
    float m2 = ((-1) * a2) / b2;

    float n1 = c1 / b1;
    float n2 = c2 / b2;

    float x1, x2, y1, y2;

    if(m1 == m2){
        if(n1 == n2){
            std::cout << "The lines are the same" << std::endl;
        }
        else{
            std::cout << "The lines are parallel" << std::endl;
        }
    }
    else if(m1 == (pow(m2, -1))){
        std::cout << "The lines are perpendicular and are intersecting at the point:" << std::endl;
        x1;
    }
    else{

    }

    return 0;
}