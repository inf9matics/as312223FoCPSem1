#include <string>
#include <vector>

std::vector<bool> convertCharBinaryVectorToBoolVector(std::vector<char> chars){
    std::vector<bool> bools;

    for(int i=0; i<chars.size(); i++){
        char c = chars.at(i);
        if(c == '0'){
            bools.push_back(false);
        }
        else{
            bools.push_back(true);
        }
    }

    return bools;
}