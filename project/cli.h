#include <map>
#include <string>
#include <iostream>
#include <vector>

std::string basicStringToString(char *basic_string){
    std::string string = basic_string;
    return string;
}

class CliArguments{
    private:
    std::string helpDialog = "Lorem ipsum dolores";
    char **cliArgumentsPointers;
    std::map<std::string, std::string> cliArguments;
    int cliArgumentsCount;
    bool prepared;

    void prepareStringMap(){
        for(int i=1; i<this->cliArgumentsCount-1; i+=2){
            this->cliArguments.insert_or_assign(basicStringToString(this->cliArgumentsPointers[i]), basicStringToString(this->cliArgumentsPointers[i+1]));
        }
    }

    std::vector<std::string> requiredParameters;

    bool checkParemeters(){
        if(this->cliArguments.size() == 0){
            std::clog << this->helpDialog;
            return false;
        }

        for(int i=0; i<this->requiredParameters.size(); i++){
            if(this->cliArguments.count(this->requiredParameters.at(i)) == 0){
                std::clog << this->requiredParameters.at(i) << " is missing";
                return false;
            }
        }
        return true;
    }

    public:
    CliArguments(int argc, char **argv, std::vector<std::string> upstreamParameters){
        this->cliArgumentsCount = argc;
        this->cliArgumentsPointers = argv;

        this->requiredParameters = upstreamParameters;

        this->prepareStringMap();

        this->prepared = this->checkParemeters();
    }

    bool isPrepared(){
        return this->prepared;
    }

    std::string at(std::string n){
        return this->cliArguments.at(n);
    }
};