#include "tMathUtilities.h"

#include <cmath>

int TMathUtilities::minOrHigher(int n, int min){
    if(n < min){
        return min;
    }
    return n;
}

int TMathUtilities::maxOrLower(int n, int max){
    if(n > max){
        return max;
    }
    return n;
}

int TMathUtilities::containInRange(int x, int min, int max){
    if(x < min){
        return min;
    }
    else if(x > max){
        return max;
    }
    else{
        return x;
    }
}