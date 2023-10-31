#include <string>

int numberOfChars(std::string str, char x){
    int counter = 0;
    for(int i=0; i<str.size(); i++){
        if(str.at(i) == x){
            counter++;
        }
    }
    return counter;
}

int main(){
    std::string str = "maslanka";

    int x = numberOfChars(str, 'a');
}