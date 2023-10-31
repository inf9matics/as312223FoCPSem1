int fibonacciIterative(int n){
    int result = 1;
    for(int i=2; i<=n; i++){
        result += i;
    }
    return result;
}

int fibonacciRecursive(int n){
    if(n <= 2){
        return 1;
    }
    else{
        return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
    }
}

int main(){
    int it = fibonacciIterative(10);
    int rec = fibonacciRecursive(10);
}