/** @file */

//
// lz77.h
// lz77
//
// Created by Adam Strączek
//

#include "cli.h"

#include <string>
#include <fstream>
#include <vector>
#include <list>

#pragma once

/**
 * @brief Class Lz77 responsible for lz77 compression.
 * @details The class won't 
 */

struct Lz77PrependData {
    long prependNumber;
    long patternLength;
    bool patternFound;
};

class Lz77Prepend {
private:
    std::list<char> bytesList;
    std::vector<std::vector<char>> bitsVectorSeparated;
    std::vector<std::vector<char>> bitsVectorSeparatedPatternLength;
    bool foundPattern;
    char startingByte;
    char ongoingByte;
    char ongoingStartingByte;

    void createPrepend(long& numberToConvert, long& patternLength);
    void prepareBitsVectorSepareted(std::vector<char>& bitsVector);
    void prepareBitsVectorSeparetedPatternLength(std::vector<char>& bitsVector);

public:
    Lz77Prepend(long numberToConvert, long patternLength);
    std::list<char>::iterator bytesListIterator;
    char next();
    int size();
    static Lz77PrependData prependDataFromBytes(std::ifstream& inputFileStream);
    };

class Lz77 {
private:
    /**
     * @brief Historical buffer for sliding window size.
     * @details #historyBufferSize is inherited from the "-n" cli parameter from #requiredParameters.\n
     * Can be larger than the file itself.\n
     * The member #historyBuffer will use at most this amount of memory (bytes).
     */
    long historyBufferSize;

    /**
     * @brief Future buffer for sliding window size.
     * @details #inputBufferSize is inherited from the "-k" cli parameter from #requiredParameters.\n
     * Can be larger than the file itself.\n
     * The member #inputBuffer will use at most this amount of memory (bytes).
     */
    long inputBufferSize;

    /**
     * @brief File buffer size.
     * @details #bufferSize is a temporal "implementation" of a file input buffer.\n
     * It's calculated from #futureBufferSize.
     */
    long bufferSize;

    std::list<char> buffer;

    bool fillBuffer();

    bool clearBuffer();

    std::string inputFileName;

    /**
     * @brief Input file stream.
     * @details #inputFileStream is inherited from the "-i" cli parameter from #requiredParameters.\n
     * It needs to exist or an exception is thrown.
     */
    std::ifstream inputFileStream;

    std::string outputFileName;

    /**
     * @brief Output file stream.
     * @details #outputFileStream is inherited from the "-o" cli parameter from #requiredParameters.\n
     * It needs to be accessible, otherwise an exception is thrown.
     */
    std::ofstream outputFileStream;

    /**
     * @brief Dev variable for logging.
     * @details #log exists for outputting logs in certain scenarios in the development process.\n
     * It's not called from outside and is currently set via the constructor Lz77().
     */
    bool log;

    /*!
        @brief Function handling input file opening.
        @details This function will throw an exception if the #inputFileStream couldn't open a file.
    */
    void openInputFile();

    /*!
        @brief Function handling output file opening.
        @details This function will throw an exception if the #outputFileStream couldn't open a file.
    */
    void openOutputFile();

public:
    /*!
        @brief Constructor for the Lz77 class.
        @details This constructor prepares the object via cli handling.\n
        The constructor will throw an exception and call CliArguments::getHelpDialog() in order to write a help message.
        @param argc the number of arguments passed down from cli
        @param argv the array containing cli arguments
    */
    Lz77(std::string inputFileName, std::string outputFileName, long historyBufferSize, long inputBufferSize);

    /**
     * @brief Function returning value of argument from cli.
     * @details argument() returns the corresponding element from the internal map of #cliArguments.
     * @param i (std::string)
     * @return Value of #cliArguments map at key i (std::string)
     */
    std::string argument(std::string i);

    void compress();

    void decompress();

    void run();
    };

class Lz77CliArguments {
private:
    std::vector<std::string> requiredParameters{
        "-i",
        "-o",
        "-t",
        "-n",
        "-k"
        };
    CliArguments* cliArguments;

public:
    Lz77CliArguments(int argc, char** argv);
    Lz77* lz77;
    };