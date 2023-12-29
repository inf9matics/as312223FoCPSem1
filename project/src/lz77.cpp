#include "lz77.h"
#include "cli.h"
#include "tMathUtilities.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>

Lz77Prepend::Lz77Prepend(long numberToConvert, long patternLength) {
    if (patternLength != 0) {
        this->foundPattern = true;
        startingByte = 1 << 7;
        }
    else {
        this->foundPattern = false;
        startingByte = 0;
        }
    this->ongoingByte = 1 << 7;
    this->ongoingStartingByte = 1 << 6;

    this->createPrepend(numberToConvert, patternLength);

    this->bytesListIterator = this->bytesList.begin();
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
    this->bytesList.push_back(currentByte);
    for (int i = 1; i < this->bitsVectorSeparated.size() - 1; i++) {
        currentByte = this->ongoingByte;
        for (int j = 0; j < this->bitsVectorSeparated.at(i).size(); j++) {
            currentByte += this->bitsVectorSeparated.at(i).at(j) << (6 - j);
            }
        this->bytesList.push_back(currentByte);
        }
    currentByte = 0;
    for (int i = 0; i < this->bitsVectorSeparated.at(this->bitsVectorSeparated.size() - 1).size(); i++) {
        currentByte += this->bitsVectorSeparated.at(this->bitsVectorSeparated.size() - 1).at(i) << (6 - i);
        }
    this->bytesList.push_back(currentByte);
    if (this->foundPattern) {
        currentByte = 0;
        numberBitVector = TMathUtilities::bitVectorFromNumber(patternLength);
        this->prepareBitsVectorSeparetedPatternLength(numberBitVector);
        for (int i = 0; i < this->bitsVectorSeparatedPatternLength.size() - 1; i++) {
            currentByte += this->ongoingByte;
            for (int j = 0; j < this->bitsVectorSeparatedPatternLength.at(i).size(); j++) {
                currentByte += this->bitsVectorSeparatedPatternLength.at(i).at(j) << (6 - j);
                }
            this->bytesList.push_back(currentByte);
            }
        currentByte = 0;
        for (int i = 0; i < this->bitsVectorSeparatedPatternLength.at(this->bitsVectorSeparatedPatternLength.size() - 1).size(); i++) {
            currentByte += this->bitsVectorSeparatedPatternLength.at(this->bitsVectorSeparatedPatternLength.size() - 1).at(i) << (6 - i);
            }
        }
    this->bytesList.push_back(currentByte);
    }

char Lz77Prepend::next() {
    return *this->bytesListIterator++;
    }

int Lz77Prepend::size() {
    return this->bytesList.size();
    }

void Lz77::openInputFile() {
    try {
        this->inputFileStream.open(this->inputFileName, std::ios::binary);
        }
    catch (const std::ifstream::failure& e) {
        std::cerr << e.what();
        }
    }

void Lz77::openOutputFile() {
    try {
        this->outputFileStream.open(this->outputFileName, std::ios::binary);
        }
    catch (const std::ifstream::failure& e) {
        std::cerr << e.what();
        }
    }

Lz77::Lz77(std::string inputFileName, std::string outputFileName, std::string compressionMode, long historyBufferSize, long inputBufferSize) {
    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;
    this->compressionMode = compressionMode;
    this->historyBufferSize = historyBufferSize;
    this->inputBufferSize = inputBufferSize;

    this->bufferSize = this->historyBufferSize + this->inputBufferSize + 1;
    }

bool Lz77::fillBuffer() {
    if (this->inputFileStream.peek() == EOF) {
        return false;
        }
    while (this->buffer.size() < this->bufferSize && this->inputFileStream.peek() != EOF) {
        this->buffer.push_back(this->inputFileStream.get());
        }
    return true;
    }

void Lz77::compress() {
    this->openInputFile();
    this->openOutputFile();

    this->fillBuffer();

    std::list<char>::iterator currentByteIterator = this->buffer.begin();
    currentByteIterator++;
    if (currentByteIterator == this->buffer.end()) {
        abort;
        }
    std::list<char>::iterator historyByteIterator = this->buffer.begin();
    std::list<char>::iterator inputByteIterator = currentByteIterator;

    while (this->fillBuffer() || !this->buffer.empty()) {
        while (historyByteIterator != currentByteIterator) {
            if (*historyByteIterator == *currentByteIterator) {
                int patternLength = 1;
                int patternDistance = std::distance(historyByteIterator, currentByteIterator);
                inputByteIterator = currentByteIterator;
                historyByteIterator++;
                inputByteIterator++;
                while (*historyByteIterator == *inputByteIterator && patternLength < this->inputBufferSize) {
                    patternLength++;
                    historyByteIterator++;
                    inputByteIterator++;
                    }
                Lz77Prepend patternPrepend{ patternDistance, patternLength };
                historyByteIterator = currentByteIterator;
                std::advance(historyByteIterator, -patternDistance);
                int noPatternLength = std::distance(this->buffer.begin(), historyByteIterator);
                if (patternPrepend.size() < noPatternLength) {
                    Lz77Prepend noPatternPrepend{ noPatternLength, 0 };
                    for (int i = 0; i < noPatternPrepend.size(); i++) {
                        this->outputFileStream << *noPatternPrepend.bytesListIterator++;
                        }
                    char bufferWrite[noPatternLength];
                    std::list<char>::iterator writeByteIterator = this->buffer.begin();
                    for (int i = 0; i < noPatternLength; i++) {
                        bufferWrite[i] = *writeByteIterator++;
                        }
                    this->outputFileStream.write(bufferWrite, noPatternLength);

                    for (int i = 0; i < patternPrepend.size(); i++) {
                        this->outputFileStream << *patternPrepend.bytesListIterator++;
                        }
                    }

                else {
                    std::advance(historyByteIterator, patternLength-1);
                    }
                }
            historyByteIterator++;
            }
        currentByteIterator++;
        this->buffer.pop_front();
        historyByteIterator = this->buffer.begin();
        }

    this->inputFileStream.close();
    this->outputFileStream.close();
    }

void Lz77::decompress() {
    this->openInputFile();
    this->openOutputFile();

    this->inputFileStream.close();
    this->outputFileStream.close();
    }

void Lz77::run() {
    if (this->compressionMode == "c" || this->compressionMode == "-c") {
        this->compress();
        }
    else if (this->compressionMode == "d" || this->compressionMode == "-d") {
        this->decompress();
        }
    }

Lz77CliArguments::Lz77CliArguments(int argc, char** argv) {
    this->cliArguments = new CliArguments(argc, argv, this->requiredParameters);
    if (this->cliArguments->isPrepared()) {
        this->lz77 = new Lz77(this->cliArguments->at("-i"), this->cliArguments->at("-o"), this->cliArguments->at("-t"), std::stol(this->cliArguments->at("-n")), std::stol(this->cliArguments->at("-k")));
        }
    else {
        abort;
        }
    }