#include "tCollectionUtilities.h"

#include <vector>
#include <cmath>

std::vector<char> TCollectionUtilities::bitVectorFromNumber(long x) {
    std::vector<char> bitVector;
    while (x > 0) {
        bitVector.push_back(x % 2);
        x = x / 2;
        }
    return bitVector;
    }

void TCollectionUtilities::flipCharVector(std::vector<char>& vector) {
    int vectorMiddle = (vector.size() - 1) / 2;
    for (int i = 0; i <= vectorMiddle; i++) {
        char temp = vector.at(i);
        vector.at(i) = vector.at(vector.size() - 1 - i);
        vector.at(vector.size() - 1 - i) = temp;
        }
    }

void TCollectionUtilities::flipIntVector(std::vector<int>& vector) {
    int vectorMiddle = (vector.size() - 1) / 2;
    for (int i = 0; i <= vectorMiddle; i++) {
        char temp = vector.at(i);
        vector.at(i) = vector.at(vector.size() - 1 - i);
        vector.at(vector.size() - 1 - i) = temp;
        }
    }

long TCollectionUtilities::longFromBitVector(std::vector<int>& bitVector) {
    long result = 0;
    for (int i = 0; i < bitVector.size(); i++) {
        result += bitVector.at(i) * std::pow(2, i);
        }
    return result;
    }