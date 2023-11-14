#include "utilities.h"
#include "cli.h"

#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>

class Lz77 {
    private:
    int historyBufferSize;
    int inputBufferSize;
    std::ifstream inputFileStream;
    std::ofstream outputFileStream;

    std::vector<std::string> requiredParameters {
        "-i",
        "-o",
        "-t",
        "-n",
        "-k"
    };

    CliArguments *cliArguments;
    
    void openInputFile(){
        try{
            this->inputFileStream.open(this->cliArguments->at("-i"), std::ios::binary);
            // this->inputFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        }
        catch(const std::ifstream::failure &e){
            std::cerr << e.what();
        }      
    }

    void openOutput(){
        try{
            this->outputFileStream.open(this->cliArguments->at("-o"), std::ios::binary);
            // this->outputFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        }
        catch(const std::ifstream::failure &e){
            std::cerr << e.what();
        }      
    }

    public:
    Lz77(int argc, char **argv){
        this->cliArguments = new CliArguments {argc, argv, this->requiredParameters};

        this->inputBufferSize = std::stoi(this->cliArguments->at("-k"));
        this->historyBufferSize = std::stoi(this->cliArguments->at("-n"));
    }
    
    void compress(){
        if(this->cliArguments->isPrepared()){
            this->openInputFile();
            this->openOutput();
            char currentByte;
            char historyBuffer[this->historyBufferSize + this->inputBufferSize + 1];
            for(int i=0; i<this->historyBufferSize; i++){
                historyBuffer[i] = inputFileStream.get();
            }
            inputFileStream.get(currentByte);
            for(int j=0; j<this->inputBufferSize; j++){
                historyBuffer[this->historyBufferSize+1+j] = inputFileStream.get();
            }

            while(this->inputFileStream.get(currentByte)){
                for(int i=0; i<this->historyBufferSize; i++){
                    if (historyBuffer[i] == currentByte){
                        bool patternDone = false;
                        for(int j=1; j<this->inputBufferSize && !patternDone; j++){
                            if(historyBuffer[i+j] == currentByte){

                            }
                        }
                    }
                    else{
                        std::memmove(&historyBuffer[0], &historyBuffer[1], (this->historyBufferSize - 1) * sizeof(historyBuffer[0]));
                    }
                }
            }

            this->inputFileStream.close();
        }
    }

    void decompress(){
    
    }
};