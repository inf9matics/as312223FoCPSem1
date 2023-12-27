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
 * @details The class in itself assumes it's going to be run from cli along with parameters, therefore it has a member of class CliArguments.
 */

class Lz77Prepend {
private:
    std::vector<char> bytesVector;
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
    char at(int n);
    char next();
    int size();
    };

class Lz77 {
private:
    /**
     * @brief Historical buffer for sliding window size.
     * @details #historyBufferSize is inherited from the "-n" cli parameter from #requiredParameters.\n
     * Can be larger than the file itself.\n
     * The member #historyBuffer will use at most this amount of memory (bytes).
     */
    int historyBufferSize;

    /**
     * @brief Future buffer for sliding window size.
     * @details #inputBufferSize is inherited from the "-k" cli parameter from #requiredParameters.\n
     * Can be larger than the file itself.\n
     * The member #inputBuffer will use at most this amount of memory (bytes).
     */
    int inputBufferSize;

    /**
     * @brief Input file stream.
     * @details #inputFileStream is inherited from the "-i" cli parameter from #requiredParameters.\n
     * It needs to exist or an exception is thrown.
     */
    std::ifstream inputFileStream;

    /**
     * @brief Output file stream.
     * @details #outputFileStream is inherited from the "-o" cli parameter from #requiredParameters.\n
     * It needs to be accessible, otherwise an exception is thrown.
     */
    std::ofstream outputFileStream;

    /**
     * @brief File buffer size.
     * @details #bufferSize is a temporal "implementation" of a file input buffer.\n
     * It's calculated from #futureBufferSize.
     */
    int bufferSize;

    /**
     * @brief Dev variable for logging.
     * @details #log exists for outputting logs in certain scenarios in the development process.\n
     * It's not called from outside and is currently set via the constructor Lz77().
     */
    bool log;

    /**
     * @brief Variable containing required cli parameters.
     * @details #requiredParameters holds a set list of members:
     *  - "-i"\n
     *      This parameter governs the name of the input file.
     *  - "-o"\n
     *      This parameter governs the name of the output file.
     *  - "-t"\n
     *      This parameter should have one of 2 possible values:
     *          -# "c"\n
     *              It signifies compression mode.
     *          -# "d"\n
     *              It signifies decompression mode.
     *  - "-n"\n
     *      This parameter governs #historyBufferSize.
     *  - "-k"\n
     *      This parameter governs #inputBufferSize.
     */

    std::vector<std::string> requiredParameters;

    /**
     * @brief Member handling cli arguments.
     * @details #cliArguments is an object of class CliArguments.
     * Values for it are set in the Lz77() constructor.
     */
    CliArguments* cliArguments;

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
    Lz77(int argc, char** argv);

    /**
     * @brief Function returning value of argument from cli.
     * @details argument() returns the corresponding element from the internal map of #cliArguments.
     * @param i (std::string)
     * @return Value of #cliArguments map at key i (std::string)
     */
    std::string argument(std::string i);

    void compress();

    void decompress();
    };