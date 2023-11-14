#include "cli.h"
#include "utilities.h"

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
    int slidingWindowSize;
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

        if(this->cliArguments->isPrepared()){
                this->inputBufferSize = std::stoi(this->cliArguments->at("-k"));
            this->historyBufferSize = std::stoi(this->cliArguments->at("-n"));
            this->slidingWindowSize = this->inputBufferSize + this->historyBufferSize + 1;
        }
    }
    
    void compress(){
        if(this->cliArguments->isPrepared()){
            this->openInputFile();
            this->openOutput();
            char currentByte;
            std::string buffer;
            std::string outputBuffer;
            std::string slidingWindow;
            int rawLength = 0;
            {
                char *cbuffer;
                inputFileStream.read(cbuffer, (this->slidingWindowSize)*4);
                buffer = basicStringToString(cbuffer);
            }

            std::clog << "<Input file>" << std::endl << buffer << "</Input file>" << std::endl;
            
            int currentStart = 0;
            slidingWindow.append(buffer.substr(0, this->slidingWindowSize));
            outputBuffer.append(slidingWindow);
            while(this->inputFileStream.eof()){
                while(!buffer.empty()){
                    int currentPosition = maxOrLower(this->historyBufferSize, slidingWindow.length());
                    for(int i=0; i<currentPosition; i++){
                        if(slidingWindow.at(currentPosition) == slidingWindow.at(i)){
                            bool patternDone = false;
                            int patternLength;
                            std::string patternLink;
                            for(int j=1; j<this->inputBufferSize && !patternDone; j++){
                                if(!slidingWindow.at(currentPosition+j == slidingWindow.at(i+j))){
                                    patternDone = true;
                                    patternLength = j-1;
                                }
                            }
                            patternLink.append("<");
                            patternLink.append(std::string{});
                            patternLink.append(",");
                            patternLink.append();
                            patternLink.append(">");
                            if(patternLength < patternLink.length()){
                                outputBuffer.append(patternLink);
                            }
                            else{

                        }
                    }
                buffer.clear();
            }

            this->inputFileStream.close();
        }
    }

    void decompress(){
    
    }
};