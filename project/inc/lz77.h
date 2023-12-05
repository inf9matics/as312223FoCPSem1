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

//! Class Lz77 responsible for lz77 compression.
/*!
    The class in itself assumes it's going to be run from cli along with parameters, therefore it has a member of class CliArguments.
*/
class Lz77 {
    private:
    //! Historical buffer for sliding window size.
    /*!
        #historyBufferSize is inherited from the "-n" cli parameter from #requiredParameters.
        Can be larger than the file itself.
        The member #historyBuffer will use at most this amount of memory (bytes).
    */
    int historyBufferSize;

    //! Future buffer for sliding window size.
    /*!
        #inputBufferSize is inherited from the "-k" cli parameter from #requiredParameters.
        Can be larger than the file itself.
        The member #inputBuffer will use at most this amount of memory (bytes).
    */
    int inputBufferSize;

    //! Input file stream.
    /*!
        #inputFileStream is inherited from the "-i" cli parameter from #requiredParameters.
        It needs to exist or an exception is thrown.

    */
    std::ifstream inputFileStream;

    //! Output file stream.
    /*!
        #outputFileStream is inherited from the "-o" cli parameter from #requiredParameters.
        It needs to be accessible, otherwise an exception is thrown.
    */
    std::ofstream outputFileStream;

    //! File buffer size.
    /*!
        #bufferSize is a temporal "implementation" of a file input buffer.
        It's calculated from #futureBufferSize
    */
    int bufferSize;

    //! Sliding window buffer size.
    /*!
        #futureBufferSize is calculated from #inputBufferSize and #historyBufferSize.
    */
    int futureBufferSize;

    //! Historical buffer for sliding window.
    /*!
        #historyBuffer holds bytes that've been analyzed and should be considered for pattern searching.
        It's constantly shifting and taking variables from #futureBuffer.
    */
    std::list<char> historyBuffer;

    /*!
        @brief Function to manage memory usage of historyBuffer.
        This function makes space via removing the first element of #historyBuffer if it's close to exceeding #historyBufferSize
        @return Whether an element was removed from historyBuffer.
    */
    bool historyBufferMakeSpace();

    //! Future buffer for sliding window.
    /*!
        #futureBuffer holds bytes that are after the byte that's being analyzed as the start of the pattern.
        It's constantly shifting, giving variables to #historyBuffer and taking bytes from #inputFileStream.
    */
    std::list<char> futureBuffer;

    //! Dev variable for logging
    /*!
        #log exists for outputting logs in certain scenarios in the development process.
        It's not called from outside and is currently set via the constructor Lz77().
    */
    bool log;

    //! Variable containing required cli parameters.
    /*!
        #requiredParameters holds a set list of members:
            - "-i"\n
                This parameter governs the name of the input file.
            - "-o"\n
                This parameter governs the name of the output file.
            - "-t"\n
                This parameter should have one of 2 possible values:
                    -# "c"\n
                        It signifies compression mode.
                    -# "d"\n
                        It signifies decompression mode.
            - "-n"\n
                This parameter governs #historyBufferSize.
            - "-k"\n
                This parameter governs #inputBufferSize.
    */
    std::vector<std::string> requiredParameters;

    //! Member handling cli arguments.
    /*!
        #cliArguments is an object of class CliArguments.
        Values for it are set in the Lz77() constructor.
    */
    CliArguments *cliArguments;
    
    /*!
        @brief Function handling input file opening.
        This function will throw an exception if the #inputFileStream couldn't open a file.
    */
    void openInputFile();

    /*!
        @brief Function handling output file opening.
        This function will throw an exception if the #outputFileStream couldn't open a file.
    */
    void openOutputFile();

    public:
    /*!
        @brief Constructor for the Lz77 class.
        This constructor prepares the object via cli handling.
        The constructor will throw an exception and call CliArguments::getHelpDialog() in order to write a help message.
        @param argc the number of arguments passed down from cli
        @param argv the array containing cli arguments
    */
    Lz77(int argc, char **argv);

    std::string argument(std::string i);
    
    void compress();

    void decompress();
};