#include <iostream>
#include <random>
#include <time.h>

struct Point{
    double x;
    double y;
};

struct Square{
    Point a;
    Point b;
};

struct Circle{
    Point c;
    double r;
};

int randInt(int min, int max){
    int result;
    int range = max-min;
    result = rand() % range + 1;
    return result;
}

Point getRandomPoint(int minX, int maxX, int minY, int maxY){
    Point temp;
    temp.x = randInt(minX, maxX);
    temp.x += (double )randInt(0, 99)/100;
    temp.y = randInt(minY, maxY);
    temp.y += (double )randInt(0, 99)/100;

    return temp;
}

void fillPointsArray(Point pointArray[], int pointArraySize, int minX, int maxX, int minY, int maxY){
    for(int i=0; i<pointArraySize; i++){
        pointArray[i] = getRandomPoint(minX, maxX, minY, maxY);
    }
}

double distanceBetweenPoints(Point &a, Point &b){
    double distance;
    distance = sqrt(pow(a.x-b.x, 2)+pow(a.x-b.y, 2));
    return distance;
}

double higher(double x, double y){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}

Point middlePoint(Point &a, Point &b){
    Point result;
    result.x = higher(a.x, b.x) - (fabs(a.x-b.x)/2);
    result.y = higher(a.y, b.y) - (fabs(a.y-b.y)/2);
    return result;
}

double squareArea(Square &s){
    return (pow(distanceBetweenPoints(s.a, s.b), 2));
}

Square largerSquare(Square &s1, Square &s2){
    if(squareArea(s1) > squareArea(s2)){
        return s1;
    }
    else{
        return s2;
    }
}

double circleArea(Circle &c){
    return (M_PI * pow(c.r, 2));
}

int main(){
    srand(time(NULL));

    Point a = getRandomPoint(0, 100, 0, 100);
    Point b = getRandomPoint(0, 100, 0, 100);

    Square s;
    s.a = a;
    s.b = b;

    double sa = squareArea(s);

}