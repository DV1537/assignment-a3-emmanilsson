#include <iostream>

#include "Shape3.h"
#include "Vector3.h"


#ifndef TRIANGLE3_H
#define TRIANGLE3_H


class Triangle: public Shape
{

    private: 

        double perimeter = 0;
        int numberOfPoints; 
        Vector2f *points; 
            
    public:


        Triangle(Vector2f *sourcePointss, int amountOfPoints);
        
        ~Triangle();

        double area();

        double circumference(double distanceA, double distanceB, double distanceC);

        double* position(int numberOfPoints);

        double distance(int numberOfPoints, double centerPointX, double centerPointY);

        bool isConvex();

};

#endif // !TRIANGLE3_H