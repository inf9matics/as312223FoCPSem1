#include <vector>

#pragma once

class TMathUtilities{
    public:
    static int minOrHigher(int n, int min);
    static int maxOrLower(int n, int max);
    static int containInRange(int x, int min, int max);
    static int bitLengthToRepresentX(long x);
    static int bitAtN(long x, int n);
    static std::vector<char> bitVectorFromNumber(long x);
    static void flipCharVector(std::vector<char> &vector);
};