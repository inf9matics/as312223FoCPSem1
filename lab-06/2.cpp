#include <iostream>

int main(int argc, char **argv){
    int sum = 0;
    for(int i=1; i<argc; i++){
        int curChar = strtol(argv[i], NULL, 10);
        sum += curChar;
    }
    std::cout << "The sum equals " << sum << std::endl;
}