struct Point{
    double x;
    double y;
};

void movex(Point * a, double x){
    a->x = a->x+x;
}

int main(){
    Point p;
    p.x = 2.6546457;
    p.y = 7.436543643;

    movex(&p, 12.543643);
}