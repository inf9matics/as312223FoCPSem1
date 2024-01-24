#include "cli.h"
#include "tStringUtilities.h"

#include <string>
#include <vector>

void CliArguments::prepareStringMap() {
	for (int i = 1; i < this->cliArgumentsCount - 1; i += 2) {
		this->cliArguments[TStringUtilities::basicStringToString(this->cliArgumentsPointers[i])] = TStringUtilities::basicStringToString(this->cliArgumentsPointers[i + 1]);
	}
}

bool CliArguments::checkParemeters() {
	if (this->cliArguments.size() == 0) {
		std::clog << this->helpDialog;
		return false;
	}

	for (int i = 0; i < this->requiredParameters.size(); i++) {
		if (this->cliArguments.count(this->requiredParameters.at(i)) == 0) {
			std::clog << this->requiredParameters.at(i) << " is missing";
			return false;
		}
	}
	return true;
}

CliArguments::CliArguments(int argc, char **argv, std::vector<std::string> upstreamParameters, std::string helpDialog = "Lorem ipsum dolores") {
	this->cliArgumentsCount = argc;
	this->cliArgumentsPointers = argv;

	this->requiredParameters = upstreamParameters;

	this->prepareStringMap();

	this->prepared = this->checkParemeters();

	this->helpDialog = helpDialog;

	if (this->cliArguments.find("-h") != this->cliArguments.end() || this->cliArguments.empty()) {
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