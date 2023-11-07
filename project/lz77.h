#include <string>
#include <map>
#include <iostream>

class lz77{
    private:
    char **cliArgumentsPointers;
    std::map<std::string, std::string> cliArguments;
    int cliArgumentsCount;
    std::string helpDialog = "Lorem ipsum dolores";
    bool prepared;

    bool checkParemeters(){
        if(this->cliArguments.size() == 0){
            std::clog << this->helpDialog;
            return false;
        }

        for(int i=0; i<this->requiredParametersSize; i++){
            if(this->cliArguments.count(this->requiredParemeters[i]) == 0){
                return false;
            }
        }

        return true;
    }

    void prepareStringMap(){
        for(int i=1; i<this->cliArgumentsCount-1; i+=2){
            this->cliArguments.insert((std::string(this->cliArgumentsPointers[i])), (std::string(this->cliArgumentsPointers[i+1])));
        }
    }

    static const int requiredParametersSize = 5;
    std::string requiredParemeters[requiredParametersSize] = {
        "-i",
        "-o",
        "-t",
        "-n",
        "-k"
    };

    public:
    lz77(int argc, char **argv){
        this->cliArgumentsPointers = argv;
        this->cliArgumentsCount = argc;

        this->prepareStringMap();
        if(this->checkParemeters()){
            this->prepared = true;
        }
    }

    void compress(){

    }
};