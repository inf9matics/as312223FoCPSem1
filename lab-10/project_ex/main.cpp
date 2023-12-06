/** @file */

//
//  main.cpp
//  project_ex
//
//  Created by Agnieszka Danek on 05/12/2023.
//

#include <iostream>
#include "functions.h"

/** Main function, starting point for program execution
 
@param argc number of parameters when starting the program
@param argv an array of pointers to char arrays used when running the program

@return if the program executed successfully, 0 is returned
*/
int main(int argc, const char ** argv) {
    
    std::cout << f_x(4) << " " << f_x2(4) << std::endl;
    
    //double f1(double); //sample declaration of the f1 function taking a double and returning a double
    //Pointer to a function
    double (*wsk_fun)(double); //wsk_fun pointer to a function that takes a double and returns a double
    wsk_fun = f_x;
    double (*tab1[3]) (double); //an array of pointers to functions that take a double and return a double
    tab1[0] = f_x;
    tab1[1] = f_x2;
    tab1[2] = f_10;
    
    typedef double (*pf)(double);
    pf tab2[3];  //an array of pointers to functions that take a double and return a double
    tab2[0] = f_x;
    tab2[1] = f_x2;
    tab2[2] = f_10;
    
    std::cout << tab1[0](4) << " " << tab2[1](4) << " " <<
    tab2[2](4) << std::endl;;
    
    double a = 0;
    double b = 10;
<<<<<<< HEAD
    double res1 = integral(a, b, f_x, 0.00001);
    double res2 = integral(a, b, f_x2, 0.00001);
    
    std::cout << res1 << " " << res2 << " " << integral(a, b, f_10, 0.00001) << std::endl;
=======
    double res1 = integral(a, b, f_x, 0.000001);
    double res2 = integral(a, b, f_x2, 0.000001);
    
    std::cout << res1 << " " << res2 << " " << integral(a, b, f_10, 0.000001) << std::endl;
>>>>>>> 66cd378c5224ddf3cd2e5ad41df9536bab2313ce
    return 0;
}
