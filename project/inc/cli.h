/** @file */

#include <map>
#include <string>
#include <iostream>
#include <vector>

#pragma once

/**
 * @brief Class CliArguments reponsible for cli parameter handling.
 * @details This class is a template, and implementations need to set parameters when using the CliArguments() constructor.
 */
class CliArguments{
    private:
    /**
     * @brief Message to show when no arguments are present.
     * @details @todo Implement setting it via CliArguments().
     */
    std::string helpDialog;

    /**
     * @brief A basic array holding input from cli.
     * @details It's a temporary member, as it's quickly converted to #cliArguments.
     */
    char **cliArgumentsPointers;

    /**
     * @brief Map containing the value of key at corresponding key.
     * @details When passing parameters it treats "-a b" as such: cliArguments["-a"] = "b".
     */
    std::map<std::string, std::string> cliArguments;

    /**
     * @brief An integer used for operations on #cliArgumentsPointers.
     * @details It's generated by the cli at the moment of initializing the program.
     */
    int cliArgumentsCount;

    /**
     * @brief Bool telling whether all #requiredParameters are satisfied.
     * @details This bool is checked at the end of CliArguments().
     */
    bool prepared;

    /**
     * @brief Helper method used to prepare #cliArguments.
     * @details This function derives #cliArguments from #cliArgumentsPointers and #cliArgumentsCount.
     */
    void prepareStringMap();

    /**
     * @brief Vector containing the list of required #cliArguments entries.
     * @details This std::vector is set when calling CliArguments() by an implementation.
     */
    std::vector<std::string> requiredParameters;

    /**
     * @brief Map containing default parameters to populate #cliArguments.
     * @details This std::map is set when calling CliArguments() by an implementation.
     */
    std::map<std::string, std::string> defaultParemeters;

    /**
     * @brief Function to govern #prepared.
     * @details This function is based on #requiredParameters and #cliArguments; when a value from #requiredParameters is missing in key form in #cliArguments, it returns false.
     * @return true All parameters are present in #cliArguments.
     * @return false A parameter/Parameters are missing from #cliArguments.
     */
    bool checkParemeters();

    public:
    /**
     * @brief Construct a new Cli Arguments object
     * @details This constructor internally prepares the object and sets #prepared at the end.
     * @param argc The length of argv.
     * @param argv Basic array of C-strings.
     * @param upstreamParameters A std::vector that sets #requiredParameters.
     */
    CliArguments(int argc, char **argv, std::vector<std::string> upstreamParameters);

    /**
     * @brief Function that returns #prepared
     * @details It's not checking if it's prepared and it's public to avoid messing with #prepared.
     * @return true #prepared is true.
     * @return false #prepared is false.
     */
    bool isPrepared();

    /**
     * @brief Get the #helpDialog.
     * @details This returns #helpDialog in a std::string form.
     * @return std::string #helpDialog.
     */
    std::string getHelpDialog();

    /**
     * @brief Returns #cliArguments.at n.
     * @details This functions exists to expose #cliArguments to the implementation.
     * @param n Key at #cliArguments.
     * @return std::string Value of #cliArguments at n.
     */
    std::string at(std::string n);
};