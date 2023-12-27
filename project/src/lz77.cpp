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
    }

void Lz77::decompress() {
    }