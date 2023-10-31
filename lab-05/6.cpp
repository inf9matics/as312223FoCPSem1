void swapIntArray(int array[], int a, int b){
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
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

void sort_tab(int array[], int n){
    for(int i=0; i<n-1; i++){
        int minI = minIndexIntInArray(array, i, n);
        swapIntArray(array, i, minI);
    }
}

int main(){
    int array[10] {10, 6, 2, 9, -10, 2, 7, 3, 8, 10};

    sort_tab(array, 10);
}