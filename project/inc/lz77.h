/** @file */

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
     * @brief Sliding window buffer size.
     * @details #futureBufferSize is calculated from #inputBufferSize and #historyBufferSize.
     */
    int futureBufferSize;

    /**
     * @brief Historical buffer for sliding window.
     * @details #historyBuffer holds bytes that've been analyzed and should be considered for pattern searching.\n
     * It's constantly shifting and taking variables from #futureBuffer.
     */
    std::list<char> historyBuffer;

    /**
     * @brief Function to manage memory usage of historyBuffer.
     * @details This function makes space via removing the first element of #historyBuffer if it's close to exceeding #historyBufferSize.
     * @return true First element was removed from #historyBuffer.
     * @return false Nothing was removed.
     */
    bool historyBufferMakeSpace();

    /**
     * @brief Future buffer for sliding window.
     * @details #futureBuffer holds bytes that are after the byte that's being analyzed as the start of the pattern.\n
     * It's constantly shifting, giving variables to #historyBuffer and taking bytes from #inputFileStream.
     */
    std::list<char> futureBuffer;

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
    CliArguments *cliArguments;
    
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
    Lz77(int argc, char **argv);

    /**
     * @brief Function returning value of argument from cli.
     * @details argument() returns the corresponding element from the internal map of #cliArguments.
     * @param i the key for internal #cliArguments map
     * @return std::string value at key @p i
     */
    std::string argument(std::string i);
    
    /**
     * @brief Function responsible for file compression.
     * @details The source code resides in lz77.cpp.
     */
    void compress();

    /**
     * @brief Function responsible for file decompression.
     * @details The source code resides in lz77.cpp.
     */
    void decompress();
};