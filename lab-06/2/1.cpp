#include <fstream>
#include <random>
#include <time.h>
#include <string>
#include <iostream>

int randInt(int min, int max){
    int range = max-min;
    return (rand()%range+1);
}

void num_gen(const std::string &out_name, int n){
    std::ofstream outputFile;
    try{
        outputFile.open(out_name);
    }
    catch(std::ofstream::failure &e){
        std::cerr << e.what();
        exit;
    }
    for(int i=0; i<n; i++){
        int x = randInt(0, 9999);
        std::string s = std::to_string(x);
        outputFile << s << " ";
    }
    outputFile.close();
}

unsigned long long GetFileSize(const std::string &file_name){
    std::ifstream inputFile;
    try{
        inputFile.open(file_name, std::ios::binary);
    }
    catch(std::ifstream::failure &e){
        std::cerr << e.what();
        return 0;
    }
    long long result;
    inputFile.seekg(0, inputFile.end);
    result = inputFile.tellg();
    return result;
}

int main(){
    srand(time(NULL));

    num_gen("output", 1000);
    std::clog << GetFileSize("output") << "B";
}