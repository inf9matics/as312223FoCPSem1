#include <iostream>
#include <cmath>

int main(){

    int N;

    std::cout << "Give N: ";
    std::cin >> N;

    std::cout << "Numbers 1-N written by for:" << std::endl;
    for(int i=0; i<N; ++i){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Numbers 1-N written by while:" << std::endl;
    int i = 0;
    while(i<N){
        i++;
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Numbers N-1 written by for:" << std::endl;
    for(int i=N; i>0; i--){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Numbers N-1 written by while:" << std::endl;
    i = N;
    while(i>0){
        std::cout << i << " ";
        i--;
    }
    std::cout << std::endl;

    std::cout << std::endl;

    int start, stop, divisor;
    std::cout << "Input start: ";
    std::cin >> start;
    std::cout << "Input stop: ";
    std::cin >> stop;
    std::cout << "Input divisor: ";
    std::cin >> divisor;

    i = start;
    int iDirection;
    if(stop-start > 0){
        iDirection = 1;
    }
    else{
        iDirection = -1;
    }
    while(i != stop + iDirection){
        if(i%divisor == 0){
            std::cout << i << " ";
        }
        i += iDirection;
    }
    std::cout << std::endl;

    int base, exponent, x;
    x = 1;
    i = 1;
    std::cout << "Input base: ";
    std::cin >> base;
    std::cout << "Input exponent: ";
    std::cin >> exponent;

    if(exponent > 0){
        x = base;
    }

    while(true){
        i++;
        if(i <= exponent){
            x = x * x;
        }
        else{
            break;
        }
    }
    std::cout << "Your power is: " << x << std::endl;

    return 0;
}