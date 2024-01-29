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

template<typename T>
void TCollectionUtilities::flipVector(std::vector<T>& vector){
    auto beginningIterator = vector.begin();
    auto endingIterator = vector.end();
    endingIterator--;
    T tempValue;
    long halfVectorSize = vector.size() / 2;
    while(std::prev(beginningIterator) != endingIterator && beginningIterator != endingIterator){
        tempValue = *beginningIterator;
        *beginningIterator = *endingIterator;
        *endingIterator = tempValue;
        beginningIterator++;
        endingIterator--;
    }
}

long TCollectionUtilities::longFromBitVector(std::vector<char>& bitVector) {
    long result = 0;
    for (int i = 0; i < bitVector.size(); i++) {
        result += bitVector.at(i) * std::pow(2, i);
        }
    return result;
    }