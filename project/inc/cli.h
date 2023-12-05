#include <map>
#include <string>
#include <iostream>
#include <vector>

#pragma once

class CliArguments{
    private:
    std::string helpDialog;
    char **cliArgumentsPointers;
    std::map<std::string, std::string> cliArguments;
    int cliArgumentsCount;
    bool prepared;

    void prepareStringMap();

    std::vector<std::string> requiredParameters;

    bool checkParemeters();

    public:
    CliArguments(int argc, char **argv, std::vector<std::string> upstreamParameters);

    bool isPrepared();

    std::string getHelpDialog();

    std::string at(std::string n);
};