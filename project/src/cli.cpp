/**
 * @file cli.cpp
 * @author Adam Strączek (as312223@student.polsl.pl)
 * @brief Source code file for the implementation of cli.h.
 * @version 1.2
 */

#include "cli.h"
#include "tStringUtilities.h"

#include <string>
#include <vector>

void CliArguments::prepareStringMap() {
	for (int i = 1; i < this->cliArgumentsCount; i++) {
		std::string currentString = TStringUtilities::basicStringToString(this->cliArgumentsPointers[i]);
		if(currentString.substr(0, 2) == "--"){
			this->cliArguments[currentString] = "";
		}
		else if(currentString.substr(0, 1) == "-"){
			std::string nextString = "";
			if(i+1 < this->cliArgumentsCount){
				nextString = TStringUtilities::basicStringToString(this->cliArgumentsPointers[i+1]);
				i++;
			}
			if(nextString.substr(0, 1) == "-" || nextString == ""){
				this->cliArguments[currentString] = "";
				i--;
			}
			else{
				this->cliArguments[currentString] = nextString;
			}
		}
	}
}

std::pair<bool, std::string> CliArguments::checkParemeters() {
	if (this->cliArguments.size() == 0) {
		std::clog << this->helpDialog;
		return std::pair<bool, std::string>{false, ""};
	}

	for (int i = 0; i < this->requiredParameters.size(); i++) {
		if (this->cliArguments.count(this->requiredParameters.at(i)) == 0) {
			std::clog << this->requiredParameters.at(i) << " missing" << std::endl;
			return std::pair<bool, std::string>{false, this->requiredParameters.at(i)};
		}
	}
	return std::pair<bool, std::string>{true, ""};
}

CliArguments::CliArguments(int argc, char **argv, std::vector<std::string> upstreamParameters, std::string helpDialog = "Lorem ipsum dolores") {
	this->cliArgumentsCount = argc;
	this->cliArgumentsPointers = argv;

	this->requiredParameters = upstreamParameters;

	this->prepareStringMap();

	this->prepared = this->checkParemeters().first;

	this->helpDialog = helpDialog;

	if (this->cliArguments.find("--help") != this->cliArguments.end() || this->cliArguments.empty()) {
		this->printHelpDialog();
		this->prepared = false;
	}
}

bool CliArguments::isPrepared() { return this->prepared; }

void CliArguments::printHelpDialog() { std::cout << this->helpDialog << std::endl; }

std::string CliArguments::at(std::string n) { return this->cliArguments.at(n); }

bool CliArguments::exists(std::string n) {
	bool exists;
	exists = (this->cliArguments.find(n) != this->cliArguments.end());
	return exists;
}