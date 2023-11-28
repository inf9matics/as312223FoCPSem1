#include <iostream>

class TListElement{
    public:
    TListElement *nextElement;
    TListElement *previousElement;

    int value;

    TListElement(int x){
        this->value = x;
    }
};

class TList{
    public:
    TListElement *firstElement;

    TList(){
        this->firstElement = new TListElement(0);

        this->firstElement->previousElement = this->firstElement;
        this->firstElement->nextElement = this->firstElement;
    }

    void push_back(int x){
        TListElement *currentElement = this->firstElement->nextElement;
        while(currentElement != currentElement->nextElement){
            currentElement = currentElement->nextElement;
        }

        TListElement *newElement = new TListElement(x);
        newElement->previousElement = currentElement;
        newElement->nextElement = newElement;
        currentElement->nextElement = newElement;

    }

    void push_front(int x){
        TListElement *currentElement = this->firstElement->nextElement;
        TListElement *newElement = new TListElement(x);
        newElement->previousElement = this->firstElement;
        newElement->nextElement = currentElement;
        currentElement->previousElement = newElement;
        this->firstElement->nextElement = newElement;
    }

    void print(){
        TListElement *currentElement = this->firstElement->nextElement;
        while(currentElement != currentElement->nextElement){
            std::clog << currentElement->value << " ";
            currentElement = currentElement->nextElement;
        }
        std::clog << currentElement->value;
    }

    int at(int n){
        TListElement *currentElement = this->firstElement->nextElement;
        for(int i=0; i<n; i++){
            currentElement = currentElement->nextElement;
        }
        return currentElement->value;
    }

    void pop_back(){
        TListElement *currentElement = this->firstElement->nextElement;
        while(currentElement != currentElement->nextElement){
            currentElement = currentElement->nextElement;
        }
        currentElement = currentElement->previousElement;
        delete currentElement->nextElement;
        currentElement->nextElement = currentElement;
    }

    int front(){
        return this->firstElement->nextElement->value;
    }

    int back(){
        TListElement *currentElement = this->firstElement->nextElement;
        while(currentElement != currentElement->nextElement){
            currentElement = currentElement->nextElement;
        }
        return currentElement->value;
    }

    int *begin(){
        return &this->firstElement->nextElement->value;
    }

    int *end(){
        TListElement *currentElement = this->firstElement->nextElement;
        while(currentElement != currentElement->nextElement){
            currentElement = currentElement->nextElement;
        }
        return &currentElement->value;
    }

    void pop_at(int n){
        TListElement *currentElement = this->firstElement->nextElement;
        for(int i=0; i<n; i++){
            currentElement = currentElement->nextElement;
        }
        currentElement->previousElement->nextElement = currentElement->nextElement;
        currentElement->nextElement->previousElement = currentElement->previousElement;
        delete currentElement;
    }
};

int main(){
    TList tList;

    tList.push_back(1);
    tList.push_back(2);
    tList.push_back(3);
    tList.push_back(4);
    tList.push_front(5);

    int x = tList.at(2);
    x = tList.front();
    x = tList.back();
    x = *tList.begin();
    x = *tList.end();

    tList.print();
    std::clog << std::endl;
    tList.pop_back();
    tList.print();
    std::clog << std::endl;
    tList.pop_at(2);
    tList.print();
}