#include "lz77.h"
#include "cli.h"
#include "tMathUtilities.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

Lz77Prepend::Lz77Prepend(long numberToConvert, long patternLength) {
    if (patternLength != 0) {
        this->foundPattern = true;
        startingByte = 1 << 7;
        }
    else {
        startingByte = 0;
        }
    this->ongoingByte = 1 << 7;
    this->ongoingStartingByte = 1 << 6;

    this->createPrepend(numberToConvert, patternLength);
    }

void Lz77Prepend::prepareBitsVectorSepareted(std::vector<char>& bitsVector) {
    std::vector<char>::iterator it = bitsVector.begin();
    std::vector<char> tempVector;
    for (int i = 0; i < 6 && it != bitsVector.end(); i++) {
        tempVector.push_back(*it);
        std::advance(it, 1);
        }
    this->bitsVectorSeparated.push_back(tempVector);
    tempVector.clear();
    while (it != bitsVector.end()) {
        for (int i = 0; i < 7 && it != bitsVector.end(); i++) {
            tempVector.push_back(*it);
            std::advance(it, 1);
            }
        this->bitsVectorSeparated.push_back(tempVector);
        tempVector.clear();
        }
    }

void Lz77Prepend::prepareBitsVectorSeparetedPatternLength(std::vector<char>& bitsVector) {
    std::vector<char>::iterator it = bitsVector.begin();
    std::vector<char> tempVector;
    tempVector.clear();
    while (it != bitsVector.end()) {
        for (int i = 0; i < 7 && it != bitsVector.end(); i++) {
            tempVector.push_back(*it);
            std::advance(it, 1);
            }
        this->bitsVectorSeparatedPatternLength.push_back(tempVector);
        tempVector.clear();
        }
    }

void Lz77Prepend::createPrepend(long& numberToConvert, long& patternLength) {
    std::vector<char> numberBitVector = TMathUtilities::bitVectorFromNumber(numberToConvert);
    this->prepareBitsVectorSepareted(numberBitVector);
    numberBitVector.clear();
    char currentByte = this->startingByte;
    for (int i = 0; i < this->bitsVectorSeparated.at(0).size(); i++) {
        currentByte += bitsVectorSeparated.at(0).at(i) << (5 - i);
        }
    if (this->bitsVectorSeparated.size() > 1) {
        currentByte += this->ongoingStartingByte;
        }
    this->bytesVector.push_back(currentByte);
    for (int i = 1; i < this->bitsVectorSeparated.size() - 1; i++) {
        currentByte = this->ongoingByte;
        for (int j = 0; j < this->bitsVectorSeparated.at(i).size(); j++) {
            currentByte += this->bitsVectorSeparated.at(i).at(j) << (6 - j);
            }
        this->bytesVector.push_back(currentByte);
        }
    currentByte = 0;
    for (int i = 0; i < this->bitsVectorSeparated.at(this->bitsVectorSeparated.size() - 1).size(); i++) {
        currentByte += this->bitsVectorSeparated.at(this->bitsVectorSeparated.size() - 1).at(i) << (6 - i);
        }
    this->bytesVector.push_back(currentByte);
    if (this->foundPattern) {
        currentByte = 0;
        numberBitVector = TMathUtilities::bitVectorFromNumber(patternLength);
        this->prepareBitsVectorSeparetedPatternLength(numberBitVector);
        for (int i = 0; i < this->bitsVectorSeparatedPatternLength.size() - 1; i++) {
            currentByte += this->ongoingByte;
            for (int j = 0; j < this->bitsVectorSeparatedPatternLength.at(i).size(); j++) {
                currentByte += this->bitsVectorSeparatedPatternLength.at(i).at(j) << (6 - j);
                }
            this->bytesVector.push_back(currentByte);
            }
        currentByte = 0;
        for (int i = 0; i < this->bitsVectorSeparatedPatternLength.at(this->bitsVectorSeparatedPatternLength.size() - 1).size(); i++) {
            currentByte += this->bitsVectorSeparatedPatternLength.at(this->bitsVectorSeparatedPatternLength.size() - 1).at(i) << (6 - i);
            }
        }
    this->bytesVector.push_back(currentByte);
    }

char Lz77Prepend::at(int n) {
    return this->bytesVector.at(n);
    }

int Lz77Prepend::size() {
    return this->bytesVector.size();
    }

void Lz77::openInputFile() {
    try {
        this->inputFileStream.open(this->cliArguments->at("-i"), std::ios::binary);
        }
    catch (const std::ifstream::failure& e) {
        std::cerr << e.what();
        }
    }

void Lz77::openOutputFile() {
    try {
        this->outputFileStream.open(this->cliArguments->at("-o"), std::ios::binary);
        }
    catch (const std::ifstream::failure& e) {
        std::cerr << e.what();
        }
    }

void Lz77::fillBuffer() {
    std::clog << "Filling buffer" << std::endl;
    for (int i = 0; i < this->bufferSize && this->inputFileStream.peek() != EOF; i++) {
        this->buffer.push_back(this->inputFileStream.get());
        }
    }

Lz77::Lz77(int argc, char** argv) {
    std::string requiredParametersArray[5] = {
        "-i",
        "-o",
        "-t",
        "-n",
        "-k" };
    this->requiredParameters.insert(this->requiredParameters.end(), requiredParametersArray, requiredParametersArray + 5);
    this->cliArguments = new CliArguments{ argc, argv, this->requiredParameters };

    if (this->cliArguments->isPrepared()) {
        this->inputBufferSize = std::stoi(this->cliArguments->at("-k"));
        this->historyBufferSize = std::stoi(this->cliArguments->at("-n"));
        this->bufferSize = (this->inputBufferSize + this->historyBufferSize + 1) * 4;

        this->log = true; // Temporary
        }
    else {
        std::clog << this->cliArguments->getHelpDialog();
        std::abort();
        }
    }

std::string Lz77::argument(std::string i) {
    return this->cliArguments->at(i);
    }

void Lz77::compress() {
    this->openInputFile();
    this->openOutputFile();
    this->fillBuffer();
    std::list<char>::iterator currentByteIterator;
    currentByteIterator = this->buffer.begin();
    std::advance(currentByteIterator, 1);
    std::clog << "Advanced currentByteIterator" << std::endl;
    std::list<char>::iterator historyCurrentByteIterator;
    historyCurrentByteIterator = this->buffer.begin();
    std::list<char>::iterator futureCurrentByteIterator;
    futureCurrentByteIterator = currentByteIterator;
    int noPatternLength = 0;
    bool foundPattern = false;
    while (!this->buffer.empty()) {
        std::clog << "Iterating over buffer" << std::endl;
        while (historyCurrentByteIterator != currentByteIterator) {
            std::clog << "Iterating over historyCurrentByteIterator" << std::endl;
            if (*historyCurrentByteIterator == *currentByteIterator) {
                std::clog << "Found byte match: " << *historyCurrentByteIterator << " " << *currentByteIterator << std::endl;
                int patternDistance = std::distance(historyCurrentByteIterator, currentByteIterator);
                futureCurrentByteIterator = currentByteIterator;
                bool patternEnded = false;
                int patternLength = 1;
                for (int i = 0; i < this->inputBufferSize && futureCurrentByteIterator != this->buffer.end() && !patternEnded; i++) {
                    std::advance(historyCurrentByteIterator, 1);
                    std::advance(futureCurrentByteIterator, 1);
                    if (*historyCurrentByteIterator != *futureCurrentByteIterator) {
                        patternEnded = true;
                        }
                    else {
                        patternLength++;
                        }
                    }
                Lz77Prepend patternPrepend{ patternDistance, patternLength };
                if (patternPrepend.size() >= patternLength) {
                    foundPattern = true;
                    if (noPatternLength > 0) {
                        std::clog << "Writing noPatternPrepend" << std::endl;
                        Lz77Prepend noPatternPrepend{ noPatternLength, 0 };
                        noPatternLength = 0;
                        for (int i = 0; i < noPatternPrepend.size(); i++) {
                            this->outputFileStream << noPatternPrepend.at(i);
                            }
                        std::advance(historyCurrentByteIterator, -noPatternLength);
                        std::clog << "Writing noPattern raw bytes" << std::endl;
                        for (int i = 0; i < noPatternLength; i++) {
                            this->outputFileStream << *historyCurrentByteIterator;
                            this->buffer.pop_front();
                            }
                        historyCurrentByteIterator = this->buffer.begin();
                        }
                    std::clog << "Writing patternPrepend" << std::endl;
                    for (int i = 0; i < patternPrepend.size(); i++) {
                        this->outputFileStream << patternPrepend.at(i);
                        }
                    }
                }
            else {
                noPatternLength++;
                }
            std::advance(historyCurrentByteIterator, 1);
            }

        if (noPatternLength == this->historyBufferSize) {
            std::clog << "noPatternLength same as historyBufferSize" << std::endl;
            Lz77Prepend noPatternPrepend{ noPatternLength, 0 };
            noPatternLength = 0;
            for (int i = 0; i < noPatternPrepend.size(); i++) {
                this->outputFileStream << noPatternPrepend.at(i);
                }
            for (int i = 0; i < this->historyBufferSize; i++) {
                this->outputFileStream << *historyCurrentByteIterator;
                this->buffer.pop_front();
                std::advance(historyCurrentByteIterator, 1);
                }
            historyCurrentByteIterator = this->buffer.begin();
            }
        std::advance(currentByteIterator, 1);
        std::clog << "Advanced currentByteIterator: " << *currentByteIterator << std::endl;
        std::advance(historyCurrentByteIterator, 1);
        std::clog << "Advanced historyCurrentByteIterator: " << *historyCurrentByteIterator << std::endl;
        std::clog << "buffer.size(): " << this->buffer.size() << std::endl;
        if (this->buffer.empty()) {
            this->fillBuffer();
            }
        }
    this->inputFileStream.close();
    this->outputFileStream.close();
    }

void Lz77::decompress() {
    }