#include "lz77.h"
#include "cli.h"
#include "tMathUtilities.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include <filesystem>

bool Lz77::historyBufferMakeSpace()
{
    if (this->historyBuffer.size() >= this->historyBufferSize)
    {
        this->historyBuffer.pop_front();
        return true;
    }
    return false;
}

void Lz77::openInputFile()
{
    this->inputFileStream.exceptions(std::ifstream::failbit);
    try
    {
        this->inputFileStream.open(this->cliArguments->at("-i"), std::ios::binary);
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << e.what();
    }
}

void Lz77::openOutputFile()
{
    this->outputFileStream.exceptions(std::ofstream::failbit);
    try
    {
        this->outputFileStream.open(this->cliArguments->at("-o"), std::ios::binary);
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << e.what();
    }
}

Lz77::Lz77(int argc, char **argv)
{
    std::string requiredParametersArray[5] = {
        "-i",
        "-o",
        "-t",
        "-n",
        "-k"        
    };
    this->requiredParameters.insert(this->requiredParameters.end(), requiredParametersArray, requiredParametersArray+5);
    this->cliArguments = new CliArguments{argc, argv, this->requiredParameters};

    if (this->cliArguments->isPrepared())
    {
        this->inputBufferSize = std::stoi(this->cliArguments->at("-k"));
        this->historyBufferSize = std::stoi(this->cliArguments->at("-n"));
        this->futureBufferSize = this->inputBufferSize + this->historyBufferSize + 1;

        this->bufferSize = this->futureBufferSize * 4;

        this->log = true; // Temporary
    }
    else{
        std::clog << this->cliArguments->getHelpDialog();
        std::abort();
    }
}

std::string Lz77::argument(std::string i)
{
    return this->cliArguments->at(i);
}

void Lz77::compress()
{
    if (this->cliArguments->isPrepared())
    {
        this->openInputFile();
        this->openOutputFile();
        this->historyBuffer.clear();
        this->futureBuffer.clear();

        for (int i = 0; i < this->inputBufferSize - 1 && !this->inputFileStream.eof(); i++)
        {
            this->futureBuffer.push_back(this->inputFileStream.get());
        }

        while (!this->futureBuffer.empty())
        {
            if (!this->inputFileStream.eof())
            {
                this->futureBuffer.push_back(this->inputFileStream.get());
            }
            bool patternFound = false;
            int patternLength;
            std::list<char>::iterator historyBufferIterator = this->historyBuffer.begin();
            std::list<char>::iterator futureBufferIterator = this->futureBuffer.begin();
            for (int i = 0; i < this->historyBuffer.size() && !patternFound; i++)
            {
                if (*futureBufferIterator == *historyBufferIterator)
                {
                    bool patternDone = false;
                    for (int j = 1; (j < this->inputBufferSize) && !patternDone; j++)
                    {
                        std::advance(futureBufferIterator, 1);
                        std::advance(historyBufferIterator, 1);
                        if (*futureBufferIterator != *historyBufferIterator)
                        {
                            patternDone = true;
                            patternLength = j;
                        }
                    }
                    std::string patternString;
                    patternString.append("<");
                    patternString = patternString + std::to_string(this->historyBuffer.size() - i);
                    patternString.append(",");
                    patternString = patternString + std::to_string(patternLength);
                    if (patternLength * 2 >= patternString.length())
                    {
                        std::clog << patternString << std::endl;
                        this->outputFileStream << '<' << (this->historyBuffer.size() - i) << ',' << (patternLength);
                        patternFound = true;
                    }
                }

                // std::advance(futureBufferIterator, 1);
                // std::advance(historyBufferIterator, 1);
            }
            this->historyBufferMakeSpace();
            if (!patternFound)
            {
                this->outputFileStream << '>' << this->futureBuffer.front();
                this->historyBufferMakeSpace();
                this->historyBuffer.push_back(this->futureBuffer.front());
                this->futureBuffer.pop_front();
            }
            else
            {
                for (int i = 0; i < patternLength; i++)
                {
                    this->historyBufferMakeSpace();
                    this->historyBuffer.push_back(this->futureBuffer.front());
                    this->futureBuffer.pop_front();
                }
            }
        }
        this->inputFileStream.close();
        this->outputFileStream.close();
    }
}

void Lz77::decompress()
{
    if (this->cliArguments->isPrepared())
    {
        this->openInputFile();
        this->openOutputFile();
        this->historyBuffer.clear();
        this->futureBuffer.clear();

        for (int i = 0; (i < this->futureBufferSize - 1) && !this->inputFileStream.eof(); i++)
        {
            this->futureBuffer.push_back(this->inputFileStream.get());
        }

        while (!this->futureBuffer.empty())
        {
            if (!this->inputFileStream.eof())
            {
                this->futureBuffer.push_back(this->inputFileStream.get());
            }

            std::list<char>::iterator historyBufferIterator = this->historyBuffer.begin();
            // std::clog << "*historyBufferIterator: " << *historyBufferIterator << " | ";
            std::list<char>::iterator futureBufferIterator = this->futureBuffer.begin();
            // std::clog << "*futureBufferIterator: " << *futureBufferIterator << std::endl;

            if (*futureBufferIterator == '>' && !this->futureBuffer.empty())
            {
                std::clog << "*futureBufferIterator: " << *futureBufferIterator << " | ";
                std::advance(futureBufferIterator, 1);
                std::clog << "*futureBufferIterator: " << *futureBufferIterator << std::endl;
                this->outputFileStream << *futureBufferIterator;
                this->historyBufferMakeSpace();
                this->historyBuffer.push_back(*futureBufferIterator);
                this->futureBuffer.pop_front();
                this->futureBuffer.pop_front();
            }
            else if (*futureBufferIterator == '<' && !this->futureBuffer.empty())
            {
                std::string distanceString;
                long distance;
                do
                {
                    std::advance(futureBufferIterator, 1);
                    distanceString += *futureBufferIterator;
                    std::clog << "distanceString: " << distanceString << " | ";
                } while (*futureBufferIterator != ',');
                distanceString = distanceString.substr(0, distanceString.length() - 1);
                std::clog << "distanceString: " << distanceString << std::endl;
                distance = std::stol(distanceString);

                std::string lengthString;
                long length;
                do
                {
                    std::advance(futureBufferIterator, 1);
                    lengthString += *futureBufferIterator;
                    std::clog << "lengthString: " << lengthString << " | ";
                } while ((*futureBufferIterator != '>' && *futureBufferIterator != '<') && futureBufferIterator != this->futureBuffer.end());
                lengthString = lengthString.substr(0, lengthString.length() - 1);
                std::clog << "lengthString: " << lengthString << std::endl;
                length = std::stol(lengthString);

                historyBufferIterator = this->historyBuffer.end();
                std::advance(historyBufferIterator, -(distance));
                for (int i = 0; i < length; i++)
                {
                    this->outputFileStream << *historyBufferIterator;
                    if (this->historyBufferMakeSpace())
                    {
                        historyBufferIterator--;
                        std::clog << "historyBufferMakeSpace-- | *historyBufferIterator: " << *historyBufferIterator;
                    }
                    this->historyBuffer.push_back(*historyBufferIterator);
                    std::clog << "*historyBufferIterator: " << *historyBufferIterator << " | ";
                    historyBufferIterator++;
                }
                std::clog << std::endl;
                for (int i = 0; i < (distanceString.length() + lengthString.length() + 2); i++)
                {
                    this->futureBuffer.pop_front();
                }
            }
            else
            {
                if (futureBufferIterator != this->futureBuffer.end())
                {
                    std::advance(futureBufferIterator, 1);
                }
                this->futureBuffer.pop_front();
            }
        }

        this->inputFileStream.close();
        this->outputFileStream.close();
    }
}