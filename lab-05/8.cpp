#include <cmath>

bool isPrime(int a){
    bool prime = true;
    for(int i=2; i<=sqrt(a) && prime; i++){
        if(a%i == 0){
            prime = false;
        }
    }
    return prime;
}

int main(){
    int a = 17;

    bool prime = isPrime(a);
}