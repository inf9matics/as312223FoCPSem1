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
    if (this->bitsVectorSeparated.size() > 1) {
        for (int i = 0; i < this->bitsVectorSeparated.at(this->bitsVectorSeparated.size() - 1).size(); i++) {
            currentByte += this->bitsVectorSeparated.at(this->bitsVectorSeparated.size() - 1).at(i) << (6 - i);
            }
        this->bytesList.push_back(currentByte);
        }

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
        TMathUtilities::flipIntVector(bitVector);
        prependData.prependNumber = TMathUtilities::longFromBitVector(bitVector);
        if (prependData.patternFound) {
            TMathUtilities::flipIntVector(patternLengthBitVector);
            prependData.patternLength = TMathUtilities::longFromBitVector(patternLengthBitVector);
            }
        }

    while ((currentByte >> 7 & 1) == 1) {
        for (int i = 0; i < 7; i++) {
            bitVector.push_back(currentByte >> (6 - i) & 1);
            }
        currentByte = inputFileStream.get();
        }
    TMathUtilities::flipIntVector(bitVector);
    prependData.prependNumber = TMathUtilities::longFromBitVector(bitVector);
    while ((currentByte >> 7 & 1) == 1 && prependData.patternFound) {
        for (int i = 0; i < 7; i++) {
            patternLengthBitVector.push_back(currentByte >> (6 - i) & 1);
            }
        currentByte = inputFileStream.get();
        }
    if (prependData.patternFound) {
        TMathUtilities::flipIntVector(patternLengthBitVector);
        prependData.patternLength = TMathUtilities::longFromBitVector(patternLengthBitVector);
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
    std::list<char>::iterator currentByteIterator = this->buffer.begin();
    currentByteIterator++;
    std::list<char>::iterator historyByteIterator = this->buffer.begin();
    

    long noPatternLength = 0;
    long bytesWritten = 0;
    while(!this->buffer.empty() && currentByteIterator != this->buffer.end()){
        while(*historyByteIterator != *currentByteIterator && historyByteIterator != currentByteIterator){
            noPatternLength++;
            historyByteIterator++;
        }
        if(noPatternLength == this->buffer.size() || noPatternLength == this->historyBufferSize){
            char writeBuffer[noPatternLength];
            Lz77Prepend noPatternPrepend { noPatternLength, 0 };
            std::list<char>::iterator historyByteIteratorCopy = historyByteIterator;
            std::advance(historyByteIteratorCopy, -noPatternLength);
            for(long i=0; i<noPatternLength; i++){
                writeBuffer[i] = *historyByteIteratorCopy;
                historyByteIteratorCopy++;
            }
            for(long i=0; i<noPatternPrepend.size(); i++){
                this->outputFileStream << noPatternPrepend.next();
            }
            this->outputFileStream.write(writeBuffer, noPatternLength);
            bytesWritten += noPatternLength;
            noPatternLength = 0;
        }
        else{
            long patternLength = 1;
            long patternDistance = std::distance(historyByteIterator, currentByteIterator);
            std::list<char>::iterator inputByteIterator = currentByteIterator;
            std::list<char>::iterator historyByteIteratorCopy = historyByteIterator;
            while((*historyByteIteratorCopy == *inputByteIterator && patternLength < (bytesWritten+noPatternLength)) && (inputByteIterator != this->buffer.end() && patternLength < this->inputBufferSize)){
                patternLength++;
                historyByteIteratorCopy++;
                inputByteIterator++;
            }
            Lz77Prepend patternPrepend { patternLength, patternDistance };
            if(patternLength > patternPrepend.size()){
                Lz77Prepend noPatternPrepend { noPatternLength, 0 };
                historyByteIteratorCopy = historyByteIterator;
                std::advance(historyByteIteratorCopy, -noPatternLength);
                char writeBuffer[noPatternLength];
                for(long i=0; i<noPatternLength; i++){
                    writeBuffer[i] = *historyByteIteratorCopy;
                    historyByteIteratorCopy++;
                }
                for(long i=0; i<noPatternPrepend.size(); i++){
                    this->outputFileStream << noPatternPrepend.next();
                }
                this->outputFileStream.write(writeBuffer, noPatternLength);
                for(long i=0; i<patternPrepend.size(); i++){
                    this->outputFileStream << patternPrepend.next();
                }
                bytesWritten += noPatternLength + patternLength;
                noPatternLength = 0;
            }
        }
        currentByteIterator++;
        this->fillBuffer();
        if(std::distance(this->buffer.begin(), currentByteIterator) == this->historyBufferSize){
            this->buffer.pop_front();
        }
        historyByteIterator = this->buffer.begin();
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