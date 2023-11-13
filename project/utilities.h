#include <cmath>

int minOrHigher(int n, int min){
    if(n < min){
        return min;
    }
    return n;
}