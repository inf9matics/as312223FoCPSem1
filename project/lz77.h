// #include "utilities.h"
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
    int bufferSize;
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
        this->bufferSize = this->inputBufferSize + this->historyBufferSize + 1;
    }
    
    void compress(){
        if(this->cliArguments->isPrepared()){
            this->openInputFile();
            this->openOutput();
            char currentByte;
            std::string buffer;
            std::string slidingWindow;
            int rawLength = 0;

            char **cbuffer;
            inputFileStream.read(cbuffer, (this->bufferSize)*);

            while(this->inputFileStream.get(currentByte)){
                bool patternFound = false;
                int patternLength;
                for(int i=0; i<historyBufferSize && !patternFound; i++){
                    if(buffer[historyBufferSize+1] == buffer[i]){
                        patternFound = true;
                        bool patternDone = false;
                        for(int j=1; j<this->inputBufferSize && !patternDone; j++){
                            if(!buffer[i+j] == buffer[historyBufferSize+1]){
                                patternDone = true;
                                patternLength = j-1;
                            }
                        }
                    }
                }
                if(!patternFound){

                }
            }

            this->inputFileStream.close();
        }
    }

    void decompress(){
    
    }
};