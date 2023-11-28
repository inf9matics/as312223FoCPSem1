void reverseArray(int *array, int arraySize){
    int *lastPointer = array + arraySize - 1;
    for(int i=0; i<(arraySize/2); i++){
        *lastPointer = *lastPointer + *array;
        *array = *lastPointer - *array;
        *lastPointer = *lastPointer - *array;
        *lastPointer--;
        *array++;
    }
}

int main(){
    int array[5] = {1, 2, 3, 4, 5};

    reverseArray(array, 5);
}