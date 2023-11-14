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

int containInRange(int x, int min, int max){
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