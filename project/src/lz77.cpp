#include "lz77.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

#include "cli.h"
#include "tCollectionUtilities.h"
#include "tMathUtilities.h"

Lz77Prepend::Lz77Prepend(long patternDistance, long patternLength) {
	if (patternDistance != 0) {
		this->prependData.patternFound = true;
		startingByte = 1 << 7;
	} else {
		this->prependData.patternFound = false;
		startingByte = (char)0;
	}
	this->prependData.patternDistance = patternDistance;
	this->prependData.patternLength = patternLength;
	this->ongoingByte = 1 << 7;
	this->ongoingStartingByte = 1 << 6;

	this->createPrepend();

	this->bytesListIterator = this->bytesList.begin();
}

long Lz77Prepend::distance() { return this->prependData.patternDistance; }

long Lz77Prepend::length() { return this->prependData.patternLength; }

void Lz77Prepend::prepareBitsVectorSepareted(std::vector<char> &bitsVector) {
	std::vector<char>::iterator it = bitsVector.begin();
	std::vector<char> tempVector;
	for (int i = 0; i < 6 && it != bitsVector.end(); i++) {
		tempVector.push_back(*it);
		std::advance(it, 1);
	}
	this->bitsVectorSeparatedPatternDistance.push_back(tempVector);
	tempVector.clear();
	while (it != bitsVector.end()) {
		for (int i = 0; i < 7 && it != bitsVector.end(); i++) {
			tempVector.push_back(*it);
			std::advance(it, 1);
		}
		this->bitsVectorSeparatedPatternDistance.push_back(tempVector);
		tempVector.clear();
	}
}

void Lz77Prepend::prepareBitsVectorSeparetedPatternLength(std::vector<char> &bitsVector) {
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
	std::vector<char> numberBitVector = TCollectionUtilities::bitVectorFromNumber(this->prependData.patternDistance);
	this->prepareBitsVectorSepareted(numberBitVector);
	numberBitVector.clear();
	char currentByte = this->startingByte;
	for (int i = 0; i < this->bitsVectorSeparatedPatternDistance.at(0).size(); i++) {
		currentByte += bitsVectorSeparatedPatternDistance.at(0).at(i) << (5 - i);
	}
	if (this->bitsVectorSeparatedPatternDistance.size() > 1) {
		currentByte += this->ongoingStartingByte;
	}
	this->bytesList.push_back(currentByte);
	for (int i = 1; i < this->bitsVectorSeparatedPatternDistance.size() - 1; i++) {
		currentByte = this->ongoingByte;
		for (int j = 0; j < this->bitsVectorSeparatedPatternDistance.at(i).size(); j++) {
			currentByte += this->bitsVectorSeparatedPatternDistance.at(i).at(j) << (6 - j);
		}
		this->bytesList.push_back(currentByte);
	}
	currentByte = 0;
	if (this->bitsVectorSeparatedPatternDistance.size() > 1) {
		for (int i = 0; i < this->bitsVectorSeparatedPatternDistance.at(this->bitsVectorSeparatedPatternDistance.size() - 1).size(); i++) {
			currentByte += this->bitsVectorSeparatedPatternDistance.at(this->bitsVectorSeparatedPatternDistance.size() - 1).at(i) << (6 - i);
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

char Lz77Prepend::next() { return *this->bytesListIterator++; }

int Lz77Prepend::size() { return this->bytesList.size(); }

Lz77PrependData Lz77Prepend::prependDataFromIfstream(std::ifstream &inputFileStream) {
	Lz77PrependData prependData;
	std::vector<char> bitVector;
	std::vector<char> patternLengthBitVector;
	char currentByte;
	currentByte = inputFileStream.get();
	prependData.patternFound = false;
	if ((currentByte >> 7 & 1) == 1) {
		prependData.patternFound = true;
	}

	bool prependContinue = false;
	if ((currentByte >> 6 & 1) == 1) {
		prependContinue = true;
	}

	if (prependData.patternFound) {
		for (int i = 0; i < 6; i++) {
			bitVector.push_back((currentByte >> (5 - i)) & 1);
		}
		prependContinue = false;
		if (((currentByte >> 6) & 1) == 1) {
			prependContinue = true;
			currentByte = inputFileStream.get();
		}
		while (prependContinue) {
			for (int i = 0; i < 7; i++) {
				bitVector.push_back((currentByte >> (6 - i)) & 1);
			}
			prependContinue = false;
			if (((currentByte >> 7) & 1) == 1) {
				prependContinue = true;
				currentByte = inputFileStream.get();
			}
		}

		currentByte = inputFileStream.get();
		prependData.patternDistance = TCollectionUtilities::longFromBitVector(bitVector);

		prependContinue = false;
		if ((currentByte >> 7 & 1) == 1) {
			prependContinue = true;
		}
		do {
			for (int i = 0; i < 7; i++) {
				patternLengthBitVector.push_back((currentByte >> (6 - i)) & 1);
			}
			prependContinue = false;
			if (((currentByte >> 7) & 1) == 1) {
				prependContinue = true;
				currentByte = inputFileStream.get();
			}
		} while (prependContinue);

		prependData.patternLength = TCollectionUtilities::longFromBitVector(patternLengthBitVector);

	} else {
		prependData.patternDistance = 0;
		prependData.patternLength = 1;
	}

	return prependData;
}

void Lz77::openInputFile() {
	this->inputFileStream.open(this->inputFileName, std::ios::binary);
	if (!this->inputFileStream.good()) {
		throw this->outputFileStream.rdstate();
	}
}

void Lz77::openOutputFile() {
	this->outputFileStream.open(this->outputFileName, std::ios::binary);
	if (!this->outputFileStream.good()) {
		throw this->outputFileStream.rdstate();
	}
}

Lz77::Lz77(std::string inputFileName, std::string outputFileName, long historyBufferSize, long inputBufferSize) {
	this->inputFileName = inputFileName;
	this->outputFileName = outputFileName;
	this->historyBufferSize = historyBufferSize;
	this->inputBufferSize = inputBufferSize;

	this->windowSize = this->historyBufferSize + this->inputBufferSize;

	this->inputFileStreamBuffer = new char[this->windowSize * 256];
	this->inputFileStream.rdbuf()->pubsetbuf(this->inputFileStreamBuffer, this->windowSize * 256);
}

Lz77::~Lz77(){
	delete this->inputFileStreamBuffer;
}

bool Lz77::fillBuffer() {
	try {
		if (this->inputFileStream.peek() == EOF) {
			return false;
		}
		while (this->window.size() <= this->windowSize && this->inputFileStream.peek() != EOF) {
			this->window.push_back(this->inputFileStream.get());
		}
		return true;
	} catch (const std::ifstream::failure &e) {
		throw e.what();
	}
}

void Lz77::compress() {
	this->openInputFile();
	this->openOutputFile();

	this->window.clear();

	this->fillBuffer();

	long patternsWritten = 0;
	long predictedDataSize = 0;

	std::list<char>::iterator currentIterator = this->window.begin();
	while (!this->window.empty() && currentIterator != this->window.end()) {
		Lz77Match currentMatch = this->findLongestMatch(currentIterator);
		if (!currentMatch.foundPattern) {
			this->outputFileStream << (char)0;
			this->outputFileStream << *currentIterator;
			predictedDataSize += 2;
		} else {
			patternsWritten++;
			for (int i = 0; i < currentMatch.patternPrepend->size(); i++) {
				this->outputFileStream << currentMatch.patternPrepend->next();
				predictedDataSize++;
			}
			for (long i = 1; i < currentMatch.patternPrepend->length(); i++) {
				if (std::next(currentIterator) != this->window.end()) {
					currentIterator++;
				}
				this->window.pop_front();
			}
		}
		currentIterator++;
		if (std::distance(this->window.begin(), currentIterator) >= this->historyBufferSize) {
			this->window.pop_front();
		}
		this->fillBuffer();
	}

	std::clog << "patternsWritten: " << patternsWritten << std::endl;
	std::clog << "predictedDataSize: " << predictedDataSize << std::endl;

	this->inputFileStream.close();
	this->outputFileStream.close();
}

void Lz77::decompress() {
	this->openInputFile();
	this->openOutputFile();

	this->window.clear();

	long patternsFound = 0;

	do {
		Lz77PrependData prependData = Lz77Prepend::prependDataFromIfstream(this->inputFileStream);
		if (prependData.patternFound) {
			patternsFound++;
			long patternDistanceFromBufferBeginning = this->window.size() - prependData.patternDistance;
			std::list<char>::iterator writeIterator = this->window.begin();
			std::advance(writeIterator, patternDistanceFromBufferBeginning);
			for (long i = 0; i < prependData.patternLength; i++) {
				this->outputFileStream << *writeIterator;
				this->window.push_back(*writeIterator);
				writeIterator++;
				if (this->window.size() >= this->windowSize) {
					this->window.pop_front();
				}
			}
		} else {
			char byteToWrite = this->inputFileStream.get();
			this->outputFileStream << byteToWrite;
			this->window.push_back(byteToWrite);
			if (this->window.size() >= this->windowSize) {
				this->window.pop_front();
			}
		}
	} while (this->inputFileStream.peek() != EOF);

	std::clog << "patternsFound: " << patternsFound;

	this->inputFileStream.close();
	this->outputFileStream.close();
}

Lz77CliArguments::Lz77CliArguments(int argc, char **argv) {
	this->prepared = true;
	std::string helpDialog = "This is the help dialog for lz77 compression";
	this->cliArguments = std::unique_ptr<CliArguments>(new CliArguments{argc, argv, this->requiredParameters, helpDialog});
	if (this->cliArguments->isPrepared()) {
		long n;
		try {
			n = stol(this->cliArguments->at("-n"));
		} catch (const std::invalid_argument) {
			this->prepared = false;
			std::cerr << "-nIncorrect" << std::endl;
		}

		long k;
		try {
			k = stol(this->cliArguments->at("-k"));
		} catch (const std::invalid_argument) {
			this->prepared = false;
			std::cerr << "-kIncorrect" << std::endl;
		}

		if (this->prepared) {
			this->lz77 = std::unique_ptr<Lz77>(new Lz77{this->cliArguments->at("-i"), this->cliArguments->at("-o"), n, k});
			if (this->cliArguments->at("-t") == "c") {
				std::clog << "Compressing" << std::endl;
				this->lz77->compress();
			} else if (this->cliArguments->at("-t") == "d") {
				std::clog << "Decompressing" << std::endl;
				this->lz77->decompress();
			} else {
				std::cerr << "-tIncorrect" << std::endl;
			}
		}
	}
}

Lz77Match Lz77::findLongestMatch(std::list<char>::iterator currentByte) {
	std::list<Lz77Match> matches;
	std::list<char>::iterator historyIterator = this->window.begin();
	std::list<char>::iterator inputIterator = currentByte;
	while (historyIterator != currentByte) {
		historyIterator = std::find(historyIterator, currentByte, *currentByte);
		if (historyIterator != currentByte) {
			long patternLength = 1;
			long patternDistance = std::distance(historyIterator, currentByte);
			inputIterator = currentByte;
			std::list<char>::iterator historyIteratorCopy = historyIterator;
			inputIterator++;
			historyIteratorCopy++;
			while (inputIterator != this->window.end() && (*historyIteratorCopy == *inputIterator && patternLength < this->inputBufferSize)) {
				patternLength++;
				inputIterator++;
				historyIteratorCopy++;
			}
			if (patternLength > 1) {
				Lz77Match match;
				match.foundPattern = true;
				match.patternBeginning = historyIterator;
				match.patternPrepend = std::unique_ptr<Lz77Prepend>(new Lz77Prepend{patternDistance, patternLength});
				matches.push_back(match);
				for (long i = 1; i < patternLength && std::next(historyIterator) != currentByte; i++) {
					historyIterator++;
				}
			}
			historyIterator++;
		}
	}

	Lz77Match longestMatch;
	if (!matches.empty()) {
		std::list<Lz77Match>::iterator matchesIterator = matches.begin();
		longestMatch.foundPattern = matches.front().foundPattern;
		longestMatch.patternBeginning = matches.front().patternBeginning;
		longestMatch.patternPrepend = matches.front().patternPrepend;
		while (matchesIterator != matches.end()) {
			if (matchesIterator->patternPrepend->size() > longestMatch.patternPrepend->size()) {
				longestMatch.foundPattern = matchesIterator->foundPattern;
				longestMatch.patternBeginning = matchesIterator->patternBeginning;
				longestMatch.patternPrepend = matchesIterator->patternPrepend;
			}
			matchesIterator++;
		}
		if (longestMatch.patternPrepend->length() < 2) {
			longestMatch.patternPrepend = std::unique_ptr<Lz77Prepend>(new Lz77Prepend{0, 1});
			longestMatch.patternBeginning = currentByte;
			longestMatch.foundPattern = false;
		}
	} else {
		longestMatch.patternPrepend = std::unique_ptr<Lz77Prepend>(new Lz77Prepend{0, 1});
		longestMatch.patternBeginning = currentByte;
		longestMatch.foundPattern = false;
	}
	return longestMatch;
}