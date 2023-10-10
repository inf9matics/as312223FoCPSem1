#include <iostream>
#include <string>

int main(){
    int age;
    std::string name;

    int ageYoung = 18;
    int ageOld = 99;

    std::cout << "State your name: ";
    std::cin >> name;

    std::cout << "State your age: ";
    std::cin >> age;

    if(age < ageYoung){
        std::cout << "You are a kid";
    }
    else if(age > ageOld){
        std::cout << "You are old";
    }
    else {
        std::cout << "You are an adult";
    }
    std::cout << std::endl;

    return 0;
}