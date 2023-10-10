#include <iostream>

int main() // definition of the main function
{
    int a, b; // declaration of two variables of type int (integer numbers)

    a = 11;  // assigning value 11 to the variable a
    b = 33;
    std::cout << "Product of " << a << " and " << b << " is " << a*b << std::endl;
    
    a = (float) a; //a is casted to float, you can't change the type of defined variable
    std::cout << "Input a number for 'a': ";
    std::cin >> a;

    std::cout << "\'a\' and \'b\' become a char, so they\'re written out as the ASCII representation: " << a << ':' << (char) a << ' ' << b << ':' << (char) b << std::endl;

    

    return 0;
}