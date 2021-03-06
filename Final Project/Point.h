#ifndef FINAL_CH_H
#define FINAL_CH_H

#include <vector>

//used to hold point data
//more flexable and easy to read than using pairs the entire time
class Point
{
public:
    Point() : x{0}, y{0}, polar_angle{ NULL } {};
    Point(int f1, int f2) : x{ f1 }, y{ f2 }, polar_angle{ NULL }{};
    int x;
    int y;
    double polar_angle;
};


#endif //FINAL_CH_H
