#include <fstream>
#include <iostream>
#include <string.h>

int main(int argc, char **argv){
    std::string inputFile = "";
    std::string outputFile = "";

    bool correctParameters = false;
    for(int i=1; i<argc-1; i+=2){
        std::string tempString = std::string(argv[i]);
        std::string nextString = std::string(argv[i+1]);
        if(tempString == "-i"){
            inputFile = nextString;
        }
        else if(tempString == "-o"){
            outputFile = nextString;
        }
    }
    if(inputFile != "" && outputFile != ""){
        if(inputFile == outputFile){
            std::cerr << "Your files are the same" << std::endl;
        }
        else{
            std::clog << "Parameters correct" << std::endl;
            std::clog << "inputFile: " << inputFile << ", outputFile: " << outputFile << std::endl;
            correctParameters = true;
        }
    }
    else{
        std::cerr << "Insufficient parameters" << std::endl;
    }
    if(!correctParameters){
        return 0;
    }

    
}