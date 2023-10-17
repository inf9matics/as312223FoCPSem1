#include <iostream>
#include <cmath>

int main(){
    int x;
    std::cout << "Input a number: ";
    std::cin >> x;

    bool isPrime = true;
    for(int i=2; i<=sqrt(x) and isPrime; i++){
        if(x%i==0){
            isPrime = false;
        }
    }

    std::cout << "Your number is ";
    if(!isPrime){
        std::cout << "not ";
    }
    std::cout << "prime" << std::endl;

    return 0;
}