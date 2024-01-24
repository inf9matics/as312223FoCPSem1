#include "tMathUtilities.h"

#include <cmath>
#include <vector>
#include <list>

int TMathUtilities::minOrHigher(int x, int min) {
    if (x < min) {
        return min;
        }
    return x;
    }

int TMathUtilities::maxOrLower(int x, int max) {
    if (x > max) {
        return max;
        }
    return x;
    }

int TMathUtilities::containInRange(int x, int min, int max) {
    if (x < min) {
        return min;
        }
    else if (x > max) {
        return max;
        }
    else {
        return x;
        }
    }

int TMathUtilities::bitLengthToRepresentX(long x) {
    int sizeToRepresent;
    while (x > 0) {
        x = x / 2;
        sizeToRepresent++;
        }
    return sizeToRepresent;
    }

int TMathUtilities::bitAtN(long x, int n) {
    int result = (x >> (n - 1)) & 1;
    return result;
    }
