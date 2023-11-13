#include <string> //for convenience
#include <iostream>
#include <vector>

class OwnString{
    private:
    std::vector<char> charArrayVector; //use of pointer to allocate variable name
    bool palindrome;
    int length;

    public:
    void calcLength(){
        int counter = 0;
        while(charArray[counter] != '\0'){
            counter++;
        }
        length = counter;
    }

    OwnString(std::string str){
        charArray = new char[str.size()];
        int i;
        for(i=0; i<str.size(); i++){
            charArray[i] = str.at(i);
        }
        charArray[i] = '\0';

        this->calcLength();
    }

    char get(int n){
        return charArray[n];
    }

    void print(){
        for(int i=0; i<length; i++){
            std::cout << charArray[i];
        }
    }

    bool isPalindrome(){
        palindrome = true;
        for(int i=0; i<length && palindrome; i++){
            if(charArray[i] != charArray[length-1-i]){
                palindrome = false;
            }
        }
        return palindrome;
    }
};

int main(){
    OwnString str("maslanka");

    str.print();
    bool x = str.isPalindrome();
}