/**
 * @file lz77.h
 * @author Adam Strączek (as312223@student.polsl.pl)
 * @brief Header file containing objects governing compression using the Lz77 algorithm.
 * @version 2.0
 */

#include "cli.h"

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <memory>

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
    long patternDistance;

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
    /**
     * @brief List of prepared prepend bytes.
     */
    std::list<char> bytesList;

    /**
     * @brief A std::vector containing std::vector's of bits of #prependData->patternDistance.
     */
    std::vector<std::vector<char>> bitsVectorSeparatedPatternDistance;

    /**
     * @brief A std::vector containing std::vector's of bits of #prependData->patternLength.
     */
    std::vector<std::vector<char>> bitsVectorSeparatedPatternLength;

    /**
     * @brief Internal structure containing prepend data.
     */
    Lz77PrependData prependData;

    /**
     * @brief Byte containing the bits marking the start of a prepend.
     */
    char startingByte;

    /**
     * @brief Byte containing the bits marking length of a prepend.
     */
    char ongoingByte;

    /**
     * @brief Byte that's a combination of #startingByte and #ongoingByte.
     */
    char ongoingStartingByte;

    /**
     * @brief Function preparing #bytesList.
     */
    void createPrepend();

    /**
     * @brief Function setting #bitsVectorSeparatedPatternDistance.
     * @param bitsVector Pattern distance in binary form stored as a std::vector<char>.
     */
    void prepareBitsVectorSepareted(std::vector<char>& bitsVector);

    /**
     * @brief Function setting #bitsVectorSeparatedPatternLength
     * @param bitsVector Pattern length in binary form stored as a std::vector<char>.
     */
    void prepareBitsVectorSeparetedPatternLength(std::vector<char>& bitsVector);

public:
    /**
     * @brief Constructor for the Lz77Prepend class.
     * @details This constructor sets #startingByte, #ongoingByte, #ongoingStartingByte calls #createPrepend().
     * @param patternDistance Distance to pattern.
     * @param patternLength Length of pattern.
     */
    Lz77Prepend(long patternDistance, long patternLength);

    /**
     * @brief Iterator for #bytesList.
     */
    std::list<char>::iterator bytesListIterator;

    /**
     * @brief Function returning value from #bytesListIterator and advances it.
     * @return char *#bytesListIterator.
     */
    char next();

    /**
     * @brief Function returning the size of internal bytes container.
     * @return int Size of #bytesList.
     */
    int size();

    /**
     * @brief Function used for Lz77::decompress().
     * @details It reads bytes from an std::ifstream object.\n 
     * @todo Move this to Lz77.
     * @param inputFileStream passed from Lz77::inputFileStream.
     * @return Lz77PrependData prepend data.
     */
    static Lz77PrependData prependDataFromIfstream(std::ifstream& inputFileStream);

    /**
     * @brief Function returning the distance of pattern.
     * @return long Lz77Prepend::patternDistance.
     */
    long distance();

    /**
     * @brief Function returning the length of pattern.
     * @return long Lz77Prepend::patternLength.
     */
    long length();
    };

/**
 * @brief Structure containing match.
 * @details This is used in Lz77::findLongestPattern.
 */
struct Lz77Match {
    /**
     * @brief The iterator pointing in Lz77::window.
     */
    std::list<char>::iterator patternBeginning;

    /**
     * @brief An internal implementation of Lz77Pattern.
     */
    std::shared_ptr<Lz77Prepend> patternPrepend;

    /**
     * @brief Boolean saying whether a pattern was found.
     */
    bool foundPattern;
};

/**
 * @brief Class handling file compression using the lz77 algorithm.
 * @details The class locks down files only when running compress()/decompress().\n
 * It reserves memory based on #historyBufferSize and #inputBufferSize.
 */
class Lz77 {
private:
    /**
     * @brief Internal file reading buffer.
     */
    char *inputFileStreamBuffer;

    /**
     * @brief Historical window for sliding window size.
     * @details Can be larger than the file itself.
     */
    long historyBufferSize;

    /**
     * @brief Future window for sliding window size.
     * @details Can be larger than the file itself and #historyBufferSize.
     */
    long inputBufferSize;

    /**
     * @brief Byte window size.
     * @details #windowSize is a temporal "implementation" of a file input window.\n
     * It's calculated from #inputBufferSize and #historyBufferSize at Lz77().
     */
    long windowSize;

    /**
     * @brief Byte window.
     * @details This container holds bytes utilized in the sliding window algorithm.
     */
    std::list<char> window;

    /**
     * @brief Function filling #window.
     * @details It fills #window based on whether or not it reserves the amount of memory specified via #windowSize.
     * @return true The function has added an element to #window.
     * @return false The function did nothing.
     */
    bool fillBuffer();

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

    /**
     *  @brief Function handling input file opening.
     *  @details This function will throw an exception if the #inputFileStream couldn't open a file.
     */
    void openInputFile();

    /**
     *  @brief Function handling output file opening.
     *  @details This function will throw an exception if the #outputFileStream couldn't open a file.
     */
    void openOutputFile();

    /**
     * @brief Function returning the longest match found in current #window (or no match).
     * @return Lz77Match Match information.
     */
    Lz77Match findLongestMatch(std::list<char>::iterator currentByte);

public:
    /**
     *  @brief Constructor for the Lz77 class.
     *  @details This constructor reserver space for #inputFileStreamBuffer and sets parameters.
     *  @param inputFileName Name of the input file.
     *  @param outputFileName Name of the output file.
     *  @param historyBufferSize Size of the data to keep in memory.
     *  @param inputBufferSize Size of the maximum possible pattern.
     */
    Lz77(std::string inputFileName, std::string outputFileName, long historyBufferSize, long inputBufferSize);

    /**
     * @brief Destructor for the Lz77 class.
     * @details This destructors removes internal pointers.
     */
    ~Lz77();

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
         */
    std::unique_ptr<CliArguments> cliArguments;

    /**
     * @brief Variable marking that the arguments are correct and the object is ready for execution.
     */
    bool prepared;

public:
    /**
     * @brief Construct a new Lz77CliArguments object and run Lz77::compress() or Lz77::decompress().
     * @details It calls CliArguments() and Lz77() internally.
     * @param argc Cli argument count.
     * @param argv Cli argument table.
     */
    Lz77CliArguments(int argc, char** argv);

    /**
     * @brief Internal implementation of Lz77.
     */
    std::unique_ptr<Lz77> lz77;
    };