#include "lz77.h"

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
	if (patternLength != 0) {
		this->prependData.patternFound = true;
		startingByte = (char)-128;
	} else {
		this->prependData.patternFound = false;
		startingByte = (char)0;
	}
	this->prependData.patternDistance = patternDistance;
	this->prependData.patternLength = patternLength;
	this->ongoingByte = (char)-128;
	this->ongoingStartingByte = (char)128;

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

char Lz77Prepend::next() { return *this->bytesListIterator++; }

int Lz77Prepend::size() { return this->bytesList.size(); }

Lz77PrependData Lz77Prepend::prependDataFromIfstream(std::ifstream &inputFileStream) {
	Lz77PrependData prependData;
	std::vector<int> bitVector;
	std::vector<int> patternLengthBitVector;
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
	try {
		this->inputFileStream.open(this->inputFileName, std::ios::binary);
	} catch (const std::ifstream::failure &e) {
		std::cerr << e.what();
	}
}

void Lz77::openOutputFile() {
	try {
		this->outputFileStream.open(this->outputFileName, std::ios::binary);
	} catch (const std::ifstream::failure &e) {
		std::cerr << e.what();
	}
}

Lz77::Lz77(std::string inputFileName, std::string outputFileName, long historyBufferSize, long inputBufferSize) {
	this->inputFileName = inputFileName;
	this->outputFileName = outputFileName;
	this->historyBufferSize = historyBufferSize;
	this->inputBufferSize = inputBufferSize;

	this->bufferSize = this->historyBufferSize + this->inputBufferSize;
}

bool Lz77::fillBuffer() {
	if (this->inputFileStream.peek() == EOF) {
		return false;
	}
	while (this->buffer.size() <= this->bufferSize && this->inputFileStream.peek() != EOF) {
		this->buffer.push_back(this->inputFileStream.get());
	}
	return true;
}

void Lz77::compress() {
	this->openInputFile();
	this->openOutputFile();

	this->buffer.clear();

	this->fillBuffer();

	long patternsWritten = 0;
	long predictedDataSize = 0;

	std::list<char>::iterator currentIterator = this->buffer.begin();
	while (!this->buffer.empty() && currentIterator != this->buffer.end()) {
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
				if (std::next(currentIterator) != this->buffer.end()) {
					currentIterator++;
				}
				this->buffer.pop_front();
			}
		}
		currentIterator++;
		if (!this->buffer.empty() && std::distance(this->buffer.begin(), currentIterator) >= this->historyBufferSize) {
			this->buffer.pop_front();
		}
		this->fillBuffer();
	}

	std::clog << "patternsWritten: " << patternsWritten << std::endl;
	std::clog << "predictedDataSize: " << predictedDataSize;

	this->inputFileStream.close();
	this->outputFileStream.close();
}

void Lz77::decompress() {
	this->openInputFile();
	this->openOutputFile();

	this->buffer.clear();

	long patternsFound = 0;

	do {
		Lz77PrependData prependData = Lz77Prepend::prependDataFromIfstream(this->inputFileStream);
		if (prependData.patternFound) {
			patternsFound++;
			long patternDistanceFromBufferBeginning = this->buffer.size() - prependData.patternDistance;
			std::list<char>::iterator writeIterator = this->buffer.begin();
			std::advance(writeIterator, patternDistanceFromBufferBeginning);
			for (long i = 0; i < prependData.patternLength; i++) {
				this->outputFileStream << *writeIterator;
				this->buffer.push_back(*writeIterator);
				writeIterator++;
				if (this->buffer.size() >= this->bufferSize) {
					this->buffer.pop_front();
				}
			}
		} else {
			char byteToWrite = this->inputFileStream.get();
			this->outputFileStream << byteToWrite;
			this->buffer.push_back(byteToWrite);
			if (this->buffer.size() >= this->bufferSize) {
				this->buffer.pop_front();
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
			std::cerr << "-nIncorrect";
			std::cout << "-n needs to be a number";
		}

		long k;
		try {
			k = stol(this->cliArguments->at("-k"));
		} catch (const std::invalid_argument) {
			this->prepared = false;
			std::cerr << "-kIncorrect";
			std::clog << "-k needs to be a number";
		}

		if (this->prepared) {
			this->lz77 = std::unique_ptr<Lz77>(new Lz77{this->cliArguments->at("-i"), this->cliArguments->at("-o"), n, k});
			if (this->cliArguments->at("-t") == "c") {
				std::clog << "Compressing";
				this->lz77->compress();
			} else if (this->cliArguments->at("-t") == "d") {
				std::clog << "Decompressing";
				this->lz77->decompress();
			} else {
				std::cerr << "-tIncorrect";
				std::clog << "-t needs to be either '-c' or '-d'";
			}
		}

	} else {
		this->prepared = false;
		std::cerr << "notEnoughArguments";
	}
}

Lz77Match Lz77::findLongestMatch(std::list<char>::iterator currentByte) {
	std::list<Lz77Match> matches;
	std::list<char>::iterator historyIterator = this->buffer.begin();
	std::list<char>::iterator inputIterator = currentByte;
	while (historyIterator != currentByte) {
		if (*historyIterator == *currentByte) {
			long patternLength = 1;
			long patternDistance = std::distance(historyIterator, currentByte);
			std::list<char>::iterator historyIteratorCopy = historyIterator;
			inputIterator = currentByte;
			historyIteratorCopy++;
			inputIterator++;
			while (inputIterator != this->buffer.end() && (*inputIterator == *historyIteratorCopy && patternLength < this->inputBufferSize)) {
				patternLength++;
				inputIterator++;
				historyIteratorCopy++;
			}
			Lz77Match match;
			match.patternBeginning = historyIterator;
			match.patternPrepend = std::shared_ptr<Lz77Prepend>(new Lz77Prepend{patternDistance, patternLength});
			match.foundPattern = true;
			matches.push_back(match);
			for (long i = 1; i < patternLength && std::next(historyIterator) != currentByte; i++) {
				historyIterator++;
			}
		}
		historyIterator++;
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
			longestMatch.patternPrepend = std::unique_ptr<Lz77Prepend>(new Lz77Prepend{1, 0});
			longestMatch.patternBeginning = currentByte;
			longestMatch.foundPattern = false;
		}
	} else {
		longestMatch.patternPrepend = std::unique_ptr<Lz77Prepend>(new Lz77Prepend{1, 0});
		longestMatch.patternBeginning = currentByte;
		longestMatch.foundPattern = false;
	}
	return longestMatch;
}