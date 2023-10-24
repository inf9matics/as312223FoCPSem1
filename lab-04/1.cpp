#include <iostream>
#include <cmath>
#include <random>
#include <time.h>

int randInt(int min, int max){
    int range = max-min;
    int result = rand()%range + min;
    return result;
}

void fillIntArray(int array[], int n, int min, int max){
    for(int i=0; i<n; i++){
        array[i]=randInt(min, max);
    }
}

void printIntArray(int array[], int n){
    for(int i=0; i<n; i++){
        std::cout << "[" << i << "] : "<< array[i] << std::endl;
    }
    std::cout << std::endl;
}

int minIndexIntInArray(int array[], int a, int b){
    int minI = a;
    for(int i=a+1; i<b; i++){
        if(array[i] < array[minI]){
            minI = i;
        }
    }
    return minI;
}

void swapIntArray(int array[], int a, int b){
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void sortIntArray(int array[], int n){
    for(int i=0; i<n-1; i++){
        int minI = minIndexIntInArray(array, i, n);
        swapIntArray(array, i, minI);
    }
}

int main(){
    srand(time(NULL));
    const int n=10;
    int oneDimensionalArray[n];
    fillIntArray(oneDimensionalArray, n, 0, 100);
    printIntArray(oneDimensionalArray, n);
    int min = oneDimensionalArray[minIndexIntInArray(oneDimensionalArray, 0, n)];
    std::cout << "min: "<< min << std::endl;
    sortIntArray(oneDimensionalArray, n);
    printIntArray(oneDimensionalArray, n);
}