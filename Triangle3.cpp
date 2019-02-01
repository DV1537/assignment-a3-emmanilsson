#include <iostream>
#include <cmath>
#include <fstream>

#include "Triangle3.h"

Triangle::Triangle(Vector2f *sourcePoints, int numberOfPoints)
{

    this->points = new Vector2f[(numberOfPoints / 2)];

    for (int i = 0; i < (numberOfPoints / 2); i++)
    {
        this->points[i].x = sourcePoints[i].x;
        this->points[i].y = sourcePoints[i].y;
    }
}

double Triangle::area()
{

    int n = 0;
    double areaOfTriangle;
    areaOfTriangle = ((points[n].x * (points[1].y - points[2].y)) + (points[1].x * (points[2].y - points[n].y)) + (points[2].x * (points[n].y - points[1].y))) / 2;

    areaOfTriangle = abs(areaOfTriangle);

    //Print the area with a decimal precision of 3
    areaOfTriangle = areaOfTriangle * pow(10, 3);
    areaOfTriangle = floor(areaOfTriangle);
    areaOfTriangle = areaOfTriangle / pow(10, 3);

    std::cout << "\nArea: " << areaOfTriangle;

    return areaOfTriangle;
}

double Triangle::circumference(double distanceA, double distanceB, double distanceC)
{

    distanceA = pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2);
    distanceB = pow(points[1].x - points[2].x, 2) + pow(points[1].y - points[2].y, 2);
    distanceC = pow(points[2].x - points[0].x, 2) + pow(points[2].y - points[0].y, 2);

    distanceA = sqrt(distanceA);
    distanceB = sqrt(distanceB);
    distanceC = sqrt(distanceC);

    this->perimeter = distanceA + distanceB + distanceC;

    perimeter = perimeter * pow(10, 3);
    perimeter = floor(perimeter);
    perimeter = perimeter / pow(10, 3);

    std::cout << "\nCircumference: " << this->perimeter;

    return this->perimeter;
}

double *Triangle::position(int numberOfPoints)
{

    double centroidX, centroidY;

    centroidX = (points[0].x + points[1].x + points[2].x) / 3;
    centroidY = (points[0].y + points[1].y + points[2].y) / 3;

    centroidX = centroidX * pow(10, 3); //Print centroids with 3 decimal digits
    centroidX = floor(centroidX);
    centroidX = centroidX / pow(10, 3);

    centroidY = centroidY * pow(10, 3);
    centroidY = floor(centroidY);
    centroidY = centroidY / pow(10, 3);

    std::cout << "\nCentroid: "
              << "(" << centroidX << ", " << centroidY << ")";

    distance(numberOfPoints, centroidX, centroidY);

    double *center;

    delete center;

    center = NULL;
    return center;
}

double Triangle::distance(int numberOfPoints, double centerPointX, double centerPointY)
{

    double x1, x2, y1, y2;
    double distanceX, distanceY, distance;

    x1 = centerPointX;
    y1 = centerPointY;

    //Since there is only one shape, I chose to compare the centroid to another point far away from the centroid
    x2 = (numberOfPoints / 2) + 10;
    y2 = (numberOfPoints / 2) + 10;

    //I'm using the distance formula, previously used for calculating circumference for triangle and polygon
    distanceX = pow(x1 - x2, 2);
    distanceY = pow(y1 - y2, 2);

    distance = distanceX + distanceY;
    distance = sqrt(distance);

    distance = distance * pow(10, 3);
    distance = floor(distance);
    distance = distance / pow(10, 3);

    std::cout << "\nDistance: " << distance;

    return distance;
}

Triangle::~Triangle()
{
    delete[] points;
    points = nullptr;
}