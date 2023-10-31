#include <iostream>

void print_tab_reverse_recursive(int arr[], int n){
    std::cout << arr[n-1] << " ";
    if(n-1 > 0){
        print_tab_reverse_recursive(arr, n-1);
    }
}

int main(){
    int array[10] {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};

    print_tab_reverse_recursive(array, 10);
}