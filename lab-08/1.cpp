#include <set>
#include <unordered_set>
#include <random>
#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>

std::string trim(const std::string& s){
    std::size_t first = s.find_first_not_of("(){}[]?!\'\"-.,;:*");
    std::size_t last = s.find_last_not_of("(){}[]?!\'\"-.,;:*");

    if (first != std::string::npos and last != std::string::npos)
        return s.substr(first, last - first + 1);
    else
        return std::string("");
}

void wordsInFile(std::map<std::string, int> &map, std::ifstream &fileStream){
    while(!fileStream.eof()){
        std::string word;
        fileStream >> word;
        word = trim(word);
        if(map.count(word) == 0){
            map.insert_or_assign(word, 1);
        }
        else{
            map.insert_or_assign(word, (map.at(word)+1));
        }
    }
}

void doubleWordsInFile(std::map<std::string, int> &map, std::ifstream &fileStream){
    while(!fileStream.eof()){
        std::string word;
        fileStream >> word;
        word = trim(word);
        std::string word2;
        fileStream >> word2;
        word2 = trim(word2);
        word.append(" ");
        word.append(word2);
        if(map.count(word) == 0){
            map.insert_or_assign(word, 1);
        }
        else{
            map.insert_or_assign(word, (map.at(word)+1));
        }
    }
}

int main(){
    std::vector<int> v {55, 32, 11, 55, 11, 11};
    std::cout << "| ";
    for(auto &element : v){
        std::cout << element << " | ";
    }
    std::cout << std::endl;

    std::set<int> s {55, 32, 11, 55, 11, 11};
    std::cout << "| ";
    for(auto &element : s){
        std::cout << element << " | ";
    }
    std::cout << std::endl;

    std::unordered_set<int> us {55, 32, 11, 55, 11, 11};
    std::cout << "| ";
    for(auto &element : us){
        std::cout << element << " | ";
    }
    std::cout << std::endl;

    std::map<int, char> m {
        std::pair<int, char>{55, 'a'},
        std::pair<int, char>{32, 'b'},
        std::pair<int, char>{11, 'c'},
        std::pair<int, char>{55, 'd'},
        std::pair<int, char>{11, 'e'},
        std::pair<int, char>{11, 'f'},
    };
    std::cout << "| ";
    for(auto &element : m){
        std::cout << element.first << " : " << element.second << " | ";
    }
    std::cout << std::endl;

    std::unordered_map<int, char> um {
        std::pair<int, char>{55, 'a'},
        std::pair<int, char>{32, 'b'},
        std::pair<int, char>{11, 'c'},
        std::pair<int, char>{55, 'd'},
        std::pair<int, char>{11, 'e'},
        std::pair<int, char>{11, 'f'},
    };
    std::cout << "| ";
    for(auto &element : um){
        std::cout << element.first << " : " << element.second << " | ";
    }
    std::cout << std::endl;

    std::map<std::string, std::string> WhoWhere;
    WhoWhere.insert_or_assign("Adam", "Pyongyang");
    WhoWhere.insert_or_assign("Barbara", "Singapore");
    WhoWhere.insert_or_assign("John", "Kyoto");
    WhoWhere.insert_or_assign("Joseph", "Toronto");
    WhoWhere.insert_or_assign("Stacy", "Berlin");
    WhoWhere["Alexander"] = "Madrid";
    WhoWhere["Grasha"] = "Warsaw";
    WhoWhere["Steven"] = "Stalingrad";
    WhoWhere["Magdalene"] = "New York";
    WhoWhere["Sasha"] = "Petersburg";
    std::cout << "| ";
    for(auto &element : WhoWhere){
        std::cout << element.first << " : " << element.second << " | ";
    }
    std::cout << std::endl;

    std::ifstream inputFileStream;
    inputFileStream.open("currentBook");
    std::map<std::string, int> wordsOccurences;
    wordsInFile(wordsOccurences, inputFileStream);
    inputFileStream.close();
    std::cout << "| ";
    for(auto &element : wordsOccurences){
        std::cout << element.first << " : " << element.second << " | ";
    }
    std::cout << std::endl;

    inputFileStream.open("currentBook");
    std::map<std::string, int> doubleWordsOccurences;
    doubleWordsInFile(doubleWordsOccurences, inputFileStream);
    inputFileStream.close();
    std::cout << "| ";
    for(auto &element : doubleWordsOccurences){
        std::cout << element.first << " : " << element.second << " | ";
    }
    std::cout << std::endl;
}