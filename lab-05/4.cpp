void swap(int &a, int &b){
    a = a + b;
    b = a - b;
    a = a - b;
}

int main(){
    int a {4};
    int b {10};

    swap(a, b);
}