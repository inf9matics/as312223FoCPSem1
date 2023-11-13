#include "utilities.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>

class lz77{
    private:
    std::string raw;
    std::string compressed;
    int historyBufferSize;
    int inputBufferSize;
    std::vector<std::string> patterns;
    std::vector<int> patternsOccurences;

    public:
    lz77(int inputBufferSize, int historyBufferSize){
        this->inputBufferSize = inputBufferSize;
        this->historyBufferSize = historyBufferSize;
    }

    void setRaw(std::string x){
        this->raw = x;
    }
    
    void compress(){
        int currentCharIndex = 0;
        std::string currentString;
        while(currentCharIndex < this->raw.size()){
            bool foundPattern = false;
            currentString = this->raw.substr(currentCharIndex, currentCharIndex+1);
            for(int i = minOrHigher(currentCharIndex-this->historyBufferSize, 0); i<currentCharIndex; i++){
                if(currentString == this->raw.substr(i, i+1)){
                    std::string tempString;
                    bool longerPattern = true;
                    for(int j = 1; j<this->inputBufferSize && longerPattern; j++){
                        tempString = this->raw.substr(i, j);
                        if()
                    }
                }
            }
        }
    }

    void setCompressed(std::vector<std::string> x){

    }

    void decompress(){
    
    }
};