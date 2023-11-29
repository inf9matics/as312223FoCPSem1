void my_swap_1(int * a, int * b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void my_swap_2(int & a, int & b){
    a = a + b;
    b = a - b;
    a = a - b;
}

int main(){
    int a = 10;
    int b = -10;

    my_swap_1(&a, &b);
    my_swap_2(a, b);
}