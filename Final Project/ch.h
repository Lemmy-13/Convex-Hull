#ifndef FINAL_CH_H
#define FINAL_CH_H

#include <vector>

class Point
        {
        public:
            Point() : x{0}, y{0} {};
            Point(float f1, float f2) : x{f1}, y{f2} {};
            float x;
            float y;
            bool operator<(Point);
            bool operator==(Point);
        };


#endif //FINAL_CH_H
