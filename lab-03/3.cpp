#include <iostream>
#include <cmath>
#include <random>
#include <time.h>

int randInt(int min, int max){
    int range = max - min + 1;
    int result = rand() % range + min;
    return result;
}

int main(){
    srand(time(NULL));
    int x, userGuess;
    x = randInt(1, 100);

    std::cout << "Guessing game" << std::endl;

    int maxGuesses = 10;
    int guesses = 0;
    bool guessed = false;
    for(int i=0; i<maxGuesses and !guessed; ++i){
        std::cout << "Guess a number: ";
        std::cin >> userGuess;
        if(userGuess > x){
            std::cout << "Your guess is greater than my number";
        }
        else if(userGuess < x){
            std::cout << "Your guess is less than my number";
        }
        else{
            guessed = true;
        }
        std::cout << std::endl << std::endl;
        guesses = i;
    }
    if(guessed){
        std::cout << "You've guessed my number!";
    }
    else{
        std::cout << "You've failed" << std::endl << "My number was: " << x;
    }
    std::cout << std::endl;
    std::cout << "Number of guesses: " << guesses << std::endl;

    return 0;
}