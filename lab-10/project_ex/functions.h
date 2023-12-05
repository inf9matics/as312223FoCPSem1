/** @file */

//
//  functions.h
//  project_ex
//
//  Created by Agnieszka Danek on 05/12/2023.
//

#ifndef funkcje_h
#define funkcje_h




/** A function that returns the value f(x) = x for a given x
  @param x function argument
  @return function value
*/
double f_x(double x); //declaration of function f_x that takes a double and returns a double

/** Function that returns the value f(x) = x*x for a given x
@param x function argument
@return function value
*/
double f_x2(double x); //declaration of function f_x2 that takes a double and returns a double


/**
 * @brief Function returning 10
 * 
 * @param x 
 * @return double 
 */
double f_10(double x);


/** Function returning the definite integral of function fun in the interval [a,b]
  @param a the beginning of the integration interval
  @param b end of the integration interval
  @param fun the integrated function
  @return definite integral of function fun on the interval [a,b]
*/
double integral(double a, double b, double (* fun)(double), double step); //declaration of the integral function that takes a double, double, and a pointer to a function that takes a double and returns a double


#endif /* funkcje_h */
