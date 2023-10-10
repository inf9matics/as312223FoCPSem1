#include <iostream>
#include <string>
#include <cmath>

int main(){
    int userChoice, codeGuess;
    int minRange = 1;
    int maxRange = 8;

    std::cout << "State a number between " << minRange << " and " << maxRange << ": ";
    std::cin >> userChoice;

    
    int minGuess = minRange;
    int maxGuess = maxRange;
    
    while(minGuess <= maxGuess){
        bool lessThan;
        char userAnswer;
        
        codeGuess = (minGuess + maxGuess) / 2;
        
        std::cout << "Is your number less than " << codeGuess << "? (y/n)" << std::endl;
        std::cin >> userAnswer;

        if(userAnswer == 'y'){
            lessThan = true;
        }
        else{
            lessThan = false;
        }

        if(lessThan){
            maxGuess = codeGuess - 1;
        }
        else{
            minGuess = codeGuess +  1;
        }
    }

    std::cout << "Your number is " << codeGuess << std::endl;

    return 0;
}