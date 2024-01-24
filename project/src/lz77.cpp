#include "lz77.h"
#include "cli.h"
#include "tMathUtilities.h"
#include "tCollectionUtilities.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>

Lz77Prepend::Lz77Prepend(long numberToConvert, long patternLength) {
    if (patternLength != 0) {
        this->prependData.patternFound = true;
        startingByte = 1 << 7;
        }
    else {
        this->prependData.patternFound = false;
        startingByte = 0;
        }
    this->prependData.prependNumber = numberToConvert;
    this->prependData.patternLength = patternLength;
    this->ongoingByte = 1 << 7;
    this->ongoingStartingByte = 1 << 6;

    this->createPrepend();

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

void Lz77Prepend::createPrepend() {
    std::vector<char> numberBitVector = TCollectionUtilities::bitVectorFromNumber(this->prependData.prependNumber);
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
    if (this->bitsVectorSeparated.size() > 1) {
        for (int i = 0; i < this->bitsVectorSeparated.at(this->bitsVectorSeparated.size() - 1).size(); i++) {
            currentByte += this->bitsVectorSeparated.at(this->bitsVectorSeparated.size() - 1).at(i) << (6 - i);
            }
        this->bytesList.push_back(currentByte);
        }

    if (this->prependData.patternFound) {
        currentByte = 0;
        numberBitVector = TCollectionUtilities::bitVectorFromNumber(this->prependData.patternLength);
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
        this->bytesList.push_back(currentByte);
        }
    }

char Lz77Prepend::next() {
    return *this->bytesListIterator++;
    }

int Lz77Prepend::size() {
    return this->bytesList.size();
    }

Lz77PrependData Lz77Prepend::prependDataFromBytes(std::ifstream& inputFileStream) {
    Lz77PrependData prependData;
    std::vector<int> bitVector;
    std::vector<int> patternLengthBitVector;
    char currentByte;
    currentByte = inputFileStream.get();
    if ((currentByte >> 7 & 1) == 1) {
        prependData.patternFound = true;
        }
    else {
        prependData.patternFound = false;
        }

    for (int i = 0; i < 5; i++) {
        bitVector.push_back(currentByte >> (4 - i) & 1);
        }
    if (prependData.patternFound) {
        for (int i = 0; i < 5; i++) {
            patternLengthBitVector.push_back(currentByte >> (4 - i) & 1);
            }
        }

    if ((currentByte >> 6 & 1) == 0) {
        TCollectionUtilities::flipIntVector(bitVector);
        prependData.prependNumber = TCollectionUtilities::longFromBitVector(bitVector);
        if (prependData.patternFound) {
            TCollectionUtilities::flipIntVector(patternLengthBitVector);
            prependData.patternLength = TCollectionUtilities::longFromBitVector(patternLengthBitVector);
            }
        }

    while ((currentByte >> 7 & 1) == 1) {
        for (int i = 0; i < 7; i++) {
            bitVector.push_back(currentByte >> (6 - i) & 1);
            }
        currentByte = inputFileStream.get();
        }
    TCollectionUtilities::flipIntVector(bitVector);
    prependData.prependNumber = TCollectionUtilities::longFromBitVector(bitVector);
    while ((currentByte >> 7 & 1) == 1 && prependData.patternFound) {
        for (int i = 0; i < 7; i++) {
            patternLengthBitVector.push_back(currentByte >> (6 - i) & 1);
            }
        currentByte = inputFileStream.get();
        }
    if (prependData.patternFound) {
        TCollectionUtilities::flipIntVector(patternLengthBitVector);
        prependData.patternLength = TCollectionUtilities::longFromBitVector(patternLengthBitVector);
        }
    return prependData;
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

Lz77::Lz77(std::string inputFileName, std::string outputFileName, long historyBufferSize, long inputBufferSize) {
    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;
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

    std::list<char>::iterator windowCurrentIterator = this->buffer.begin();

    std::advance(windowCurrentIterator, 1);

    long noPatternLength = 0;
    long bytesInBufferAlreadyWritten = 0;
    while(!this->buffer.empty()){
        Lz77Match currentLongestMatch = this->findLongestMatch(windowCurrentIterator);
        windowCurrentIterator++;
        for(long i=0; i<=currentLongestMatch.patternPrepend->size(); i++){
            this->buffer.pop_front();
            char inputByte = this->inputFileStream.get();
            if(inputByte != EOF){
                buffer.push_back(inputByte);
            }
        }
    }

    this->inputFileStream.close();
    this->outputFileStream.close();
    }

void Lz77::decompress() {
    this->openInputFile();
    this->openOutputFile();

    char currentByte;
    std::list<char> bitList;
    currentByte = this->inputFileStream.get();
    std::list<char> buffer;
    while (this->inputFileStream.peek() != EOF) {
        Lz77PrependData prependData = Lz77Prepend::prependDataFromBytes(this->inputFileStream);
        if (prependData.patternFound) {
            std::list<char>::iterator bufferIterator = buffer.end();
            std::advance(bufferIterator, -prependData.prependNumber);
            while (bufferIterator != buffer.end()) {
                this->outputFileStream << *bufferIterator;
                bufferIterator++;
                }
            }
        else {
            char writeBuffer[prependData.prependNumber];
            this->inputFileStream.read(writeBuffer, prependData.prependNumber);
            this->outputFileStream.write(writeBuffer, prependData.prependNumber);
            for (int i = 0; i < prependData.prependNumber; i++) {
                buffer.push_back(writeBuffer[i]);
                }
            }
        if (buffer.size() > this->historyBufferSize) {
            buffer.pop_front();
            }
        }

    this->inputFileStream.close();
    this->outputFileStream.close();
    }

Lz77CliArguments::Lz77CliArguments(int argc, char** argv) {
    std::string helpDialog = "This is the help dialog for lz77 compression";
    this->cliArguments = new CliArguments(argc, argv, this->requiredParameters, helpDialog);
    if (this->cliArguments->isPrepared()) {
        this->lz77 = new Lz77(this->cliArguments->at("-i"), this->cliArguments->at("-o"), std::stol(this->cliArguments->at("-n")), std::stol(this->cliArguments->at("-k")));
        if (this->cliArguments->at("-t") == "c") {
            std::clog << "Compressing";
            this->lz77->compress();
            }
        else if (this->cliArguments->at("-t") == "d") {
            std::clog << "Decompressing";
            this->lz77->decompress();
            }
        }
    else {
        abort;
        }
    }

Lz77Match Lz77::findLongestMatch(std::list<char>::iterator currentByte){
    std::list<Lz77Match> matches;
    std::list<char>::iterator historyIterator = this->buffer.begin();
    std::list<char>::iterator inputIterator = currentByte;
    while(historyIterator != currentByte){
        if(*historyIterator == *currentByte){
            long patternLength = 1;
            long patternDistance = std::distance(historyIterator, currentByte);
            std::list<char>::iterator historyIteratorCopy = historyIterator;
            inputIterator = currentByte;
            historyIteratorCopy++;
            if(std::next(inputIterator) != this->buffer.end()){
                inputIterator++;
            }
            while(*inputIterator == *historyIteratorCopy){
                patternLength++;
                if(std::next(inputIterator) != this->buffer.end()){
                    inputIterator++;
                }
                historyIteratorCopy++;
            }
            Lz77Prepend patternPrepend { patternLength, patternDistance };
            Lz77Match match;
            match.patternBeginning = historyIterator;
            match.patternPrepend = &patternPrepend;
            matches.push_back(match);
            for(long i=0; i<patternLength && std::next(historyIterator) != currentByte; i++){
                historyIterator++;
            }
        }
        historyIterator++;
    }

    Lz77Match longestMatch;
    if(!matches.empty()){
        std::list<Lz77Match>::iterator matchesIterator = matches.begin();
        longestMatch = matches.front();
        while(matchesIterator != matches.end()){
            if(matchesIterator->patternPrepend->size() > longestMatch.patternPrepend->size()){
                longestMatch = *matchesIterator;
            }
            matchesIterator++;
        }
    }
    else{
        Lz77Prepend noPatternPrepend { std::distance(this->buffer.begin(), currentByte), 0 };
        longestMatch.patternPrepend = &noPatternPrepend;
        longestMatch.patternBeginning = this->buffer.begin();
    }
    return longestMatch;
}