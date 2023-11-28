#include <iostream>

void printArrayByPointer(double *array, int arraySize){
    for(int i=0; i<arraySize; i++){
        double &ref {*array};
        std::cout << ref << " ";
        *array++;
    }
    std::cout << std::endl;
}

int main(){
    double doubleArray[5] = {1.2, 2.1, 3.4, 4.8, 5.654645};

    printArrayByPointer(doubleArray, 5);
}