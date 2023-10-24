#include <iostream>
#include <cmath>
#include <iomanip>

void printIntArray(int array[], int n){
    for(int i=0; i<n; i++){
        std::cout << "[" << i << "] : "<< array[i] << std::endl;
    }
    std::cout << std::endl;
}

void multiplicationTableHex(int n){
    int array[n][n];

    int w = 1;
    int temp = n*n;

    while(temp > 0){
        w++;
        temp = temp/16;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            array[i][j] = (i+1) * (j+1); 
        }
    }

    std::cout << std::setw(w) << " " << "|";
    for(int i=0; i<n; i++){
        std::cout << std::setw(w) << std::hex << i+1;
    }
    std::cout << std::endl;

    for(int i=0; i<w*(n+1)+1; i++){
        std::cout << "-";
    }
    std::cout << std::endl;

    for(int i=0; i<n; i++){
        std::cout << std::setw(w) << std::hex << i+1 << "|";
        for(int j=0; j<n; j++){
            std::cout << std::setw(w) << std::hex << array[i][j];
        }
        std::cout << std::endl;
    }
}

int main(){
    int n=42;

    multiplicationTableHex(n);
}