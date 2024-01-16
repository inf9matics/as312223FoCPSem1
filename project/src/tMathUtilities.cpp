#include "tMathUtilities.h"

#include <cmath>
#include <vector>
#include <list>

int TMathUtilities::minOrHigher(int n, int min) {
    if (n < min) {
        return min;
        }
    return n;
    }

int TMathUtilities::maxOrLower(int n, int max) {
    if (n > max) {
        return max;
        }
    return n;
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

std::vector<char> TMathUtilities::bitVectorFromNumber(long x) {
    std::vector<char> bitVector;
    while (x > 0) {
        bitVector.push_back(x % 2);
        x = x / 2;
        }
    return bitVector;
    }

void TMathUtilities::flipCharVector(std::vector<char>& vector) {
    int vectorMiddle = (vector.size() - 1) / 2;
    for (int i = 0; i <= vectorMiddle; i++) {
        char temp = vector.at(i);
        vector.at(i) = vector.at(vector.size() - 1 - i);
        vector.at(vector.size() - 1 - i) = temp;
        }
    }

void TMathUtilities::flipIntVector(std::vector<int>& vector) {
    int vectorMiddle = (vector.size() - 1) / 2;
    for (int i = 0; i <= vectorMiddle; i++) {
        char temp = vector.at(i);
        vector.at(i) = vector.at(vector.size() - 1 - i);
        vector.at(vector.size() - 1 - i) = temp;
        }
    }

long TMathUtilities::longFromBitVector(std::vector<int>& bitVector) {
    long result = 0;
    for (int i = 1; i <= bitVector.size(); i++) {
        result += bitVector.at(i-1) * std::pow(2, i);
        }
    return result;
    }
