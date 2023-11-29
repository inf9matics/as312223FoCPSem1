#include <iostream>

int main(){
    int x = 2;
    int *ptr = &x;
    int &ref{*ptr};

    std::cout << &ref << std::endl;
    std::cout << ptr << std::endl;
    ref = *ptr * x; 
}