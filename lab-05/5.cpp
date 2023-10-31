#include <iostream>

void print_tab(int arr[], int n){
    for(int i=0; i<n; i++){
        std::cout << arr[i] << " ";
    }
}

int main(){
    int array[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print_tab(array, 10);
}