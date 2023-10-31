#include <string>

std::string getReverseString(std::string str){
    std::string result = "";
    for(int i=str.size()-1; i>=0; i--){
        result += str.at(i);
    }
    return result;
}

int main(){
    std::string str = "maslanka";

    std::string rts = getReverseString(str);
}