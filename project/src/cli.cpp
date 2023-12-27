#include "cli.h"
#include "tStringUtilities.h"

#include <vector>
#include <string>

void CliArguments::prepareStringMap()
{
    for (int i = 1; i < this->cliArgumentsCount - 1; i += 2)
    {
        this->cliArguments.insert_or_assign(TStringUtilities::basicStringToString(this->cliArgumentsPointers[i]), TStringUtilities::basicStringToString(this->cliArgumentsPointers[i + 1]));
    }
}

bool CliArguments::checkParemeters()
{
    if (this->cliArguments.size() == 0)
    {
        std::clog << this->helpDialog;
        return false;
    }

    for (int i = 0; i < this->requiredParameters.size(); i++)
    {
        if (this->cliArguments.count(this->requiredParameters.at(i)) == 0)
        {
            std::clog << this->requiredParameters.at(i) << " is missing";
            return false;
        }
    }
    return true;
}

CliArguments::CliArguments(int argc, char **argv, std::vector<std::string> upstreamParameters)
{
    this->cliArgumentsCount = argc;
    this->cliArgumentsPointers = argv;

    this->requiredParameters = upstreamParameters;

    this->prepareStringMap();

    this->prepared = this->checkParemeters();

    this->helpDialog = "Lorem ipsum dolores";
}

bool CliArguments::isPrepared()
{
    return this->prepared;
}

std::string CliArguments::getHelpDialog()
{
    return this->helpDialog;
}

std::string CliArguments::at(std::string n)
{
    return this->cliArguments.at(n);
}