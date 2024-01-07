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
 * @brief Data type used for Lz77Prepend.
 * @details It holds all variables needed for Lz77Prepend.
 */
struct Lz77PrependData {
    /**
     * @brief First number in prepend.
     * @details It's either the length of a chunk with no pattern or the length of a pattern.
     */
    long prependNumber;

    /**
     * @brief Length of pattern, if #patternFound.
     */
    long patternLength;

    /**
     * @brief Whether a pattern has been found.
     */
    bool patternFound;
    };

/**
 * @brief Class responsible for prepends for Lz77.
 * @details Prepends here mean byte markers put before chunks of raw bytes or markers signifying pattern bytes.\n 
 * - For the first byte:\n 
 *   - First bit:\n 
 *     - '0': Byte signifies a chunk of data with no pattern.\n 
 *     - '1': Byte signifies a chunk of data with a pattern.\n 
 *   - Second bit:
 *     - '0': The number this prepend holds is contained in this byte.\n 
 *     - '1': The number this prepend holds is longer than this byte.
 * - For the subsequent byte:\n 
 *   - First bit:\n 
 *     - '0': The number this prepend part holds ends on this byte.\n 
 *     - '1': The number this prepend part holds continues after this byte.\n 
 * 
 * If the prepend signifies a pattern, after the first number has reached the end\n 
 * ('0' at either the second bit in the first byte or the first bit in subsequent bytes)\n 
 * The rules are repeated but the same as for the second byte.
 */
class Lz77Prepend {
private:
    std::list<char> bytesList;
    std::vector<std::vector<char>> bitsVectorSeparated;
    std::vector<std::vector<char>> bitsVectorSeparatedPatternLength;
    Lz77PrependData prependData;
    char startingByte;
    char ongoingByte;
    char ongoingStartingByte;

    void createPrepend();
    void prepareBitsVectorSepareted(std::vector<char>& bitsVector);
    void prepareBitsVectorSeparetedPatternLength(std::vector<char>& bitsVector);

public:
    Lz77Prepend(long numberToConvert, long patternLength);
    std::list<char>::iterator bytesListIterator;
    char next();

    /**
     * @brief Returns size of internal bytes container.
     * @return int Size of #bytesList
     */
    int size();

    /**
     * @brief Function used for Lz77::decompress().
     * @details It reads bytes from an std::ifstream object.\n 
     * @todo Move this to Lz77.
     * @param inputFileStream passed from Lz77::inputFileStream.
     * @return Lz77PrependData prepend data.
     */
    static Lz77PrependData prependDataFromBytes(std::ifstream& inputFileStream);
    };

/**
 * @brief Class handling file compression using the lz77 algorithm.
 * @details The class locks down files only when running compress()/decompress().\n
 * It reserves memory based on #historyBufferSize and #inputBufferSize.
 */
class Lz77 {
private:
    /**
     * @brief Historical buffer for sliding window size.
     * @details Can be larger than the file itself.
     */
    long historyBufferSize;

    /**
     * @brief Future buffer for sliding window size.
     * @details Can be larger than the file itself and #historyBufferSize.
     */
    long inputBufferSize;

    /**
     * @brief Byte buffer size.
     * @details #bufferSize is a temporal "implementation" of a file input buffer.\n
     * It's calculated from #inputBufferSize and #historyBufferSize at Lz77().
     */
    long bufferSize;

    /**
     * @brief Byte buffer.
     * @details This container holds bytes utilized in the sliding window algorithm.
     */
    std::list<char> buffer;

    /**
     * @brief Function filling #buffer.
     * @details It fills #buffer based on whether or not it reserves the amount of memory specified via #bufferSize.
     * @return true The function has added an element to #buffer.
     * @return false The function did nothing.
     */
    bool fillBuffer();

    /**
     * @brief Function clearing #buffer.
     * @details It removes the first element of #buffer when it approaches #bufferSize.
     * @return true The function removed an element from #buffer. 
     * @return false The funciton did nothing.
     */
    bool clearBuffer();

    /**
     * @brief #inputFileStream file name.
     */
    std::string inputFileName;

    /**
     * @brief Input file stream.
     * @details It needs to exist or an exception is thrown.
     */
    std::ifstream inputFileStream;

    /**
     * @brief #outputFileStream file name.
     */
    std::string outputFileName;

    /**
     * @brief Output file stream.
     * @details It needs to be accessible, otherwise an exception is thrown.
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

    /**
     * @brief Function that compressed #inputFileStream and outputs it to #outputFileStream.
     * @details The function utilizes the lz77 (sliding window) algorithm.\n
     * It locks down #inputFileStream and #outputFileStream for the duration of its runtime.
     */
    void compress();

    /**
     * @brief Function that decompresses #inputFileStream and outputs it to #outputFileStream.
     * @details The function utilizes the lz77 (sliding window) algorithm.\n
     * It locks down #inputFileStream and #outputFileStream for the duration of its runtime.
     */
    void decompress();
    };

/**
 * @brief Composite class handling running Lz77 from cli utilizing CliArguments.
 * @details This class holds the required parameters for this particular function and runs the specified action on construction.
 */
class Lz77CliArguments {
private:
    /**
     * @brief Container with all required parameters.
     * @details They are passed to CliArguments via CliArguments().\n
     * They stand for:\n 
     * - "-i": Lz77::inputFileStream\n 
     * - "-o": Lz77::outputFileStream\n 
     * - "-t": whether to run Lz77::compress() ('c') or Lz77::decompress() ('d')\n 
     * - "-n": Lz77::historyBufferSize\n 
     * - "-k": Lz77::inputBufferSize
     */
    std::vector<std::string> requiredParameters{
        "-i",
        "-o",
        "-t",
        "-n",
        "-k"
        };
        /**
         * @brief Internal implementation of CliArguments.
         * @details It's a pointer so Lz77CliArguments() can assign a new CliArguments object to it.
         */
    CliArguments* cliArguments;

public:
    /**
     * @brief Construct a new Lz77CliArguments object and run Lz77::compress() or Lz77::decompress()
     * @details It calls CliArguments() and Lz77() internally.
     * @param argc Cli argument count.
     * @param argv Cli argument table.
     */
    Lz77CliArguments(int argc, char** argv);

    /**
     * @brief Internal implementation of Lz77.
     * @details It's a pointer so Lz77CliArguments() can assign a new Lz77 to it.
     */
    Lz77* lz77;
    };