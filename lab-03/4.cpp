#include <iostream>
#include <cmath>

int main(){
    int n, sum, min, max;
    sum = 0;
    n = 0;
    min = 0;
    max = 0;
    bool done = false;

    while(!done or n == 0){
        int x;
        std::cout << "Input a number: ";
        std::cin >> x;
        if(x > max){
            max = x;
        }
        else if(x < min){
            min = x;
        }
        n++;
        sum += x;
        bool correct = false;
        while(!correct){
            char c;
            std::cout << "Do you want to continue? (y/n): ";
            std::cin >> c;
            if((c == 'y' or c == 'n')){
                correct = true;
                if(c == 'n'){
                    done = true;
                }
            }
        }
    }

    float mean = sum/n;
    float deviation = sqrt((1/n) * ((pow(sum, 2) - pow(mean, -2))));

    std::cout << "Your data:" << std::endl << "Number of numbers: " << n << std::endl << "Mean of numbers: " << mean << std::endl << "Minimum number: " << min << std::endl << "Maximum number: " << max << std::endl << "Standard deviation: " << deviation << std::endl;

    return 0;
}