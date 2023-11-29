int * maxPointerInArray(int *array, int arraySize){
    int *max = array;
    for(int i=0; i<arraySize; i++){
        int &ref {*array};
        int &refMax {*max};
        if(refMax < ref){
            max = array;
        }
        *array++;
    }
    return max;
}

int main(){
    int array[5] = {745, 643643, 65498645, 6543, 765875};
    int *maxPointer = maxPointerInArray(array, 5);
}