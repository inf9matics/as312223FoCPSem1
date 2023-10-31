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

float maxOf7(float a, float b, float c, float d, float e, float f, float g){
    float ab;
    float cd;
    float ef;
    if(a>b){
        ab = a;
    }
    else{
        ab = b;
    }
    if(c>d){
        cd = c;
    }
    else{
        cd = d;
    }
    if(e>f){
        ef = e;
    }
    else{
        ef = f;
    }
    float abcd;
    float efg;
    if(ab>cd){
        abcd = ab;
    }
    else{
        abcd = cd;
    }
    if(ef>g){
        efg = ef;
    }
    else{
        ef = g;
    }
    if(abcd > efg){
        return abcd;
    }
    else{
        return efg;
    }
}

int main(){
    float a {1.387};
    float b {-7.643};
    float c {1.346};

    float x = maxOf3(a, b, c);
}