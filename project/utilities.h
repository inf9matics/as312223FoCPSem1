#include <cmath>

int minOrHigher(int n, int min){
    if(n < min){
        return min;
    }
    return n;
}

int maxOrLower(int n, int max){
    if(n > max){
        return max;
    }
    return n;
}