#include "cli.h"
#include "utilities.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

class Lz77 {
    private:
    int historyBufferSize;
    int inputBufferSize;

    std::ifstream inputFileStream;
    std::ofstream outputFileStream;

    int bufferSize;
    int futureBufferSize;
    std::list<char> historyBuffer;
    std::list<char> futureBuffer;

    bool log;

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
        }
        catch(const std::ifstream::failure &e){
            std::cerr << e.what();
        }      
    }

    void openOutputFile(){
        try{
            this->outputFileStream.open(this->cliArguments->at("-o"), std::ios::binary);
        }
        catch(const std::ifstream::failure &e){
            std::cerr << e.what();
        }
    }

    public:
    Lz77(int argc, char **argv){
        this->cliArguments = new CliArguments {argc, argv, this->requiredParameters};

        if(this->cliArguments->isPrepared()){
            this->inputBufferSize = std::stoi(this->cliArguments->at("-k"));
            this->historyBufferSize = std::stoi(this->cliArguments->at("-n"));
            this->futureBufferSize = this->inputBufferSize + this->historyBufferSize + 1;

            this->bufferSize = this->futureBufferSize * 4;

            this->log = true; //Temporary
        }
    }
    
    void compress(){
        if(this->cliArguments->isPrepared()){
            this->openInputFile();
            this->openOutputFile();

            for(int i=0; i<this->inputBufferSize && !this->inputFileStream.eof(); i++){
                this->futureBuffer.push_back(this->inputFileStream.get());
            }

            while(!this->futureBuffer.empty()){
                if(!this->inputFileStream.eof()){
                    this->futureBuffer.push_back(this->inputFileStream.get());
                }
                bool patternFound = false;
                int patternLength;
                std::list<char>::iterator historyBufferIterator = this->historyBuffer.begin();
                std::list<char>::iterator futureBufferIterator = this->futureBuffer.begin();
                for(int i=0; i<this->historyBuffer.size() && !patternFound; i++){
                    if(*futureBufferIterator == *historyBufferIterator){
                        bool patternDone = false;
                        for(int j=1; (j<this->inputBufferSize) && !patternDone; j++){
                            std::advance(futureBufferIterator, 1);
                            std::advance(historyBufferIterator, 1);
                            if(*futureBufferIterator != *historyBufferIterator){
                                patternDone = true;
                                patternLength = j;
                            }
                        }
                        std::string patternString;
                        patternString.append("<");
                        patternString = patternString + std::to_string(this->historyBuffer.size()-i);
                        patternString.append(",");
                        patternString = patternString + std::to_string(patternLength);
                        std::clog << patternString << std::endl;
                        if(patternLength*2 >= patternString.length()){
                            this->outputFileStream << '<' << (this->historyBuffer.size()-i) << ',' << (patternLength);
                            patternFound = true;
                        }
                    }

                    std::advance(historyBufferIterator, 1);
                }
                if(this->historyBuffer.size() >= this->historyBufferSize){
                    this->historyBuffer.pop_front();
                }
                if(!patternFound){
                    this->outputFileStream << '>' << this->futureBuffer.front();
                    if(this->historyBuffer.size() >= this->historyBufferSize){
                        this->historyBuffer.pop_front();
                    }
                    this->historyBuffer.push_back(this->futureBuffer.front());
                    this->futureBuffer.pop_front();
                }else{
                    for(int i=0; i<patternLength; i++){
                        if(this->historyBuffer.size() >= this->historyBufferSize){
                            this->historyBuffer.pop_front();
                        }
                        this->historyBuffer.push_back(this->futureBuffer.front());
                        this->futureBuffer.pop_front();
                    }
                }
            }
        }
    }

    void decompress(){
    
    }
};