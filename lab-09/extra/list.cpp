#include <iostream>
#include <random>
#include <time.h>

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
    int length;

    TList(){
        this->firstElement = new TListElement(0);

        this->firstElement->previousElement = this->firstElement;
        this->firstElement->nextElement = this->firstElement;

        length = 0;
    }

    void push_back(int x){
        length++;
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
        length++;
        TListElement *currentElement = this->firstElement->nextElement;
        TListElement *newElement = new TListElement(x);
        newElement->previousElement = this->firstElement;
        newElement->nextElement = currentElement;
        currentElement->previousElement = newElement;
        this->firstElement->nextElement = newElement;
    }

    void push_after(int x, int n){
        length++;
        TListElement *currentElement = this->firstElement->nextElement;
        TListElement *newElement = new TListElement(x);
        for(int i=0; i<n; i++){
            currentElement = currentElement->nextElement;
        }
        if(currentElement == currentElement->nextElement){
            currentElement->nextElement = newElement;
            newElement->previousElement = currentElement;
            newElement->nextElement = newElement;
        }
        else{
            newElement->previousElement = currentElement;
            newElement->nextElement = currentElement->nextElement;
            currentElement->nextElement->previousElement = newElement;
            currentElement->nextElement = newElement;
        }
    }

    void push_before(int x, int n){
        length++;
        TListElement *currentElement = this->firstElement->nextElement;
        TListElement *newElement = new TListElement(x);
        for(int i=0; i<n; i++){
            currentElement = currentElement->nextElement;
        }
        if(currentElement == currentElement->previousElement){
            currentElement = currentElement->nextElement;
            newElement->previousElement = this->firstElement;
            newElement->nextElement = currentElement;
            currentElement->previousElement = newElement;
            this->firstElement->nextElement = newElement;
        }
        else{
            newElement->previousElement = currentElement->previousElement;
            newElement->nextElement = currentElement;
            currentElement->previousElement->nextElement = newElement;
            currentElement->previousElement = newElement;
        }
    }

    void print(){
        TListElement *currentElement = this->firstElement->nextElement;
        while(currentElement != currentElement->nextElement){
            std::clog << currentElement->value << " ";
            currentElement = currentElement->nextElement;
        }
        if(currentElement != firstElement){
            std::clog << currentElement->value;
        }
    }

    int at(int n){
        TListElement *currentElement = this->firstElement->nextElement;
        for(int i=0; i<n; i++){
            currentElement = currentElement->nextElement;
        }
        return currentElement->value;
    }

    void assign_at(int x, int n){
        TListElement *currentElement = this->firstElement->nextElement;
        for(int i=0; i<n; i++){
            currentElement = currentElement->nextElement;
        }
        currentElement->value = x;
    }

    void pop_front(){
        length--;
        TListElement *currentElement = this->firstElement->nextElement->nextElement;
        this->firstElement->nextElement = currentElement;
        delete currentElement->previousElement;
        currentElement->previousElement = this->firstElement;
    }

    void pop_back(){
        length--;
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
        length--;
        TListElement *currentElement = this->firstElement->nextElement;
        for(int i=0; i<n; i++){
            currentElement = currentElement->nextElement;
        }
        currentElement->previousElement->nextElement = currentElement->nextElement;
        currentElement->nextElement->previousElement = currentElement->previousElement;
        delete currentElement;
    }

    void clear(){
        TListElement *currentElement = this->firstElement->nextElement;
        while(currentElement != currentElement->nextElement){
            currentElement = currentElement->nextElement;
        }
        while(currentElement != currentElement->previousElement){
            currentElement = currentElement->previousElement;
            delete currentElement->nextElement;
        }
        this->firstElement->nextElement = this->firstElement;
    }

    int size(){
        TListElement *currentElement = this->firstElement->nextElement;
        if(currentElement == currentElement->nextElement){
            return 0;
        }
        int n = 1;
        while(currentElement != currentElement->nextElement){
            n++;
            currentElement = currentElement->nextElement;
        }
        return n;
    }
};

int sumTList(TList &tList){
    int sum = 0;
    for(static int i=0; i<tList.size(); i++){
        sum += tList.at(i);
    }
    return sum;
}

int randomInRange(int a, int b){
    int range = b-a;
    return rand()%range+a+1;
}

int main(){
    srand(time(NULL));
    TList tList;

    int listSize = 12800;
    int listSeparateSum = 0;
    for(int i=0; i<listSize; i++){
        int x = randomInRange(-100, 100);
        tList.push_back(x);
        listSeparateSum += x;
    }

    std::clog << listSeparateSum << " " << sumTList(tList) << std::endl;

    tList.clear();
}