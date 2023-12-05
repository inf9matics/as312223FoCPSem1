#include "cli.h"

#include <string>
#include <fstream>
#include <vector>
#include <list>

#pragma once

class Lz77 {
    private:
    int historyBufferSize;
    int inputBufferSize;

    std::ifstream inputFileStream;
    std::ofstream outputFileStream;

    int bufferSize;
    int futureBufferSize;
    std::list<char> historyBuffer;

    bool historyBufferMakeSpace();

    std::list<char> futureBuffer;

    bool log;

    std::vector<std::string> requiredParameters;

    CliArguments *cliArguments;
    
    void openInputFile();

    void openOutputFile();

    public:
    Lz77(int argc, char **argv);

    std::string argument(std::string i);
    
    void compress();

    void decompress();
};