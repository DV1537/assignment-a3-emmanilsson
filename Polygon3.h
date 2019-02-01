#include <iostream>

#include "Shape3.h"
#include "Vector.h"

#ifndef POLYGON3_H
#define POLYGON3_H




class Polygon: public Shape
{

    private: 

        int numberOfPoints; 
        Vector2f *points;
        double centroids[2];


    public:


        Polygon();

        Polygon(double *pointsX, double *pointsY, int numberOfPoints);

        Polygon(Vector2f * sourcePoints, int numberOfPoints);
        ~Polygon();



        std::string getType(int numberOfPoints);

        double area(int numberOfPoints, bool isConv); 

        double circumference(int numberOfPoints);

        double* position(int numberOfPoints);

        bool isConvex(int numberOfPoints, bool shapeIsConvex);

        double distance(int numberOfPoints, double *centerPoint);



        Polygon& operator=(const Polygon &p);

        friend Polygon operator+(const Polygon &polygon1, const Polygon &polygon2);
        
        friend std::ostream &operator<<(std::ostream &stream, const Polygon &polygon);


};




#endif // !POLYGON3_H