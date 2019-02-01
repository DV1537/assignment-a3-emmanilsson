#include <iostream>

#ifndef POINT3_H
#define POINT3_H

#include "Shape3.h"
#include "Vector.h"

class Point: public Shape
{

    private:

        int numberOfPoints;
        Vector2f *points;

    public:

        Point(Vector2f* sourcePoints, int numberOfPoints);
        ~Point();

        std::string getType();


};



#endif // !POINT3_H