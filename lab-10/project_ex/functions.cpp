/** @file */

//
//  functions.cpp
//  project_ex
//
//  Created by Agnieszka Danek on 05/12/2023.
//

#include <iostream>
#include "functions.h"

// f(x)=10
double f_10(double x)
{
    return 10;
}

// f(x)=x
double f_x(double x)
{
    return x;
}

// f(x)=x*x
double f_x2(double x)
{
    return x*x;
}


// definite integral of function fun in the interval [a,b]
double integral(double a, double b, double (*fun)(double), double step)
{
    double area = 0;

    if(step>b){
        step = b;
    }

    a += step;
    if(a > b){
        a = b-step;
    }

    bool wentOver = false;
    do{
        area += step * fun(((2*a)-step)/2);
        a += step;
    }
    while(a <= b);

    return area;
}
