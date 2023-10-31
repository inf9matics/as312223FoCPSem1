float maxOf3(float a, float b, float c){
    if(a>b){
        if(a>c){
            return a;
        }
        else if(c>b){
            return c;
        }
    }
    else{
        if(b>c){
            return b;
        }
        else{
            return c;
        }
    }
}

int main(){
    float a {1.387};
    float b {-7.643};
    float c {1.346};

    float x = maxOf3(a, b, c);
}