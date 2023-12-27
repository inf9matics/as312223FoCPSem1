#include "tStringUtilities.h"
#include "tMathUtilities.h"

#include <string>

std::string TStringUtilities::basicStringToString(char *basic_string){
    std::string string = basic_string;
    return string;
}

std::string TStringUtilities::byteToBitString(char byte){
    std::string result;
    int byteInt = (int) byte;
    for(int i=8; i>0; i--){
        int currentBit = (byteInt >> (i-1)) & 1;
        result.push_back(currentBit+48);
    }
    return result;
}