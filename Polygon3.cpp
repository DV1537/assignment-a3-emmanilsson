#include <iostream>
#include <cmath>
#include <fstream>

#include "polygon3.h"

Polygon::Polygon()
{
}

Polygon::Polygon(Vector2f *sourcePoints, int numPoints)
{
    //Two constructors with different parameters too handle the arrays individually and together(the combined shape)

    Vector2f *tempPoints;

    tempPoints = new Vector2f[(numPoints / 2)];

    for (int i = 0; i < (numPoints / 2); i++)
    {
        tempPoints[i].x = sourcePoints[i].x;
        tempPoints[i].y = sourcePoints[i].y;
    }

    this->points = new Vector2f[(numPoints / 2)];

    for (int i = 0; i < (numPoints / 2); i++)
    {
        this->points[i].x = tempPoints[i].x;
        this->points[i].y = tempPoints[i].y;
    }

    numberOfPoints = numPoints;

    delete[] tempPoints;
    tempPoints = nullptr;

    delete[] sourcePoints;
    sourcePoints = nullptr;
}

Polygon::Polygon(double *pointsX, double *pointsY, int numPoints)
{

    Vector2f *tempPoints;
    tempPoints = new Vector2f[(numPoints / 2)];

    for (int i = 0; i < (numPoints / 2); i++)
    {
        tempPoints[i].x = pointsX[i];
        tempPoints[i].y = pointsY[i];
    }

    this->points = new Vector2f[(numPoints / 2)];

    for (int i = 0; i < (numPoints / 2); i++)
    {
        this->points[i].x = tempPoints[i].x;
        this->points[i].y = tempPoints[i].y;
    }

    numberOfPoints = numPoints;

    delete[] tempPoints;
    tempPoints = nullptr;

    delete[] pointsX;
    pointsX = nullptr;

    delete[] pointsY;
    pointsY = nullptr;
}

Polygon &Polygon::operator=(const Polygon &polygon3)
{

    if (this == &polygon3)
    {
        return *this;
    }

    else
    {

        numberOfPoints = polygon3.numberOfPoints;

        for (int n = 0; n < (polygon3.numberOfPoints) / 2; n++)
        {
            this->points[n].x = polygon3.points[n].x;
            this->points[n].y = polygon3.points[n].y;
        }

        return *this;
    }
}

Polygon operator+(const Polygon &polygon1, const Polygon &polygon2)
{

    int totalPoints = polygon1.numberOfPoints + polygon2.numberOfPoints;

    //Creating a new dynamic array for the new shape
    //Copy over the coordinates into the new array 
    Vector2f *myPoints;
    myPoints = new Vector2f[(totalPoints / 2)];

    for (int n = 0; n < (polygon1.numberOfPoints / 2); n++)
    {
        myPoints[n].x = polygon1.points[n].x;
        myPoints[n].y = polygon1.points[n].y;
    }

    for (int n = 0; n < (polygon2.numberOfPoints / 2); n++)
    {
        myPoints[(polygon1.numberOfPoints / 2) + n].x = polygon2.points[n].x;
        myPoints[(polygon1.numberOfPoints / 2) + n].y = polygon2.points[n].y;
    }

    bool isConv;
    //Create a new object for the new shape, passing dynamic array and points
    Polygon polygon3(myPoints, totalPoints);

    //The overloaded stream operator is "called" when printing the object 
    cout << polygon3;

    std::cout << "\nType: " << polygon3.getType(totalPoints);

    //For polygon and triangle
    if (totalPoints >= 6 )
    {
        std::cout << "\nConvex: " << polygon3.isConvex(totalPoints, isConv);
        std::cout << "\nArea: " << polygon3.area(totalPoints, isConv);
    }

    //For line and point
    else if(totalPoints == 2 ||totalPoints == 4 )
    {
        polygon3.Shape::isConvex();
        std::cout << "Area: " << polygon3.Shape::area();
    }

    return polygon3;
}

std::ostream &operator<<(std::ostream &os, const Polygon &polygon)
{

    //Print the coordinates with a precision of 3 decimal digits
    std::cout << "\nCoordinates: ";
    for (int n = 0; n < (polygon.numberOfPoints / 2); n++)
    {
        polygon.points[n].x = floor((polygon.points[n].x * pow(10, 3)));
        polygon.points[n].x = polygon.points[n].x / pow(10, 3);

        polygon.points[n].y = floor((polygon.points[n].y * pow(10, 3)));
        polygon.points[n].y = polygon.points[n].y / pow(10, 3);

        os << "(" << polygon.points[n].x << ", " << polygon.points[n].y << ") ";
    }

    os << "\n";

    return os;
}

std::string Polygon::getType(int numberOfPoints)
{
    //Find out what type the shape with combined points have
    std::string type;

    if (numberOfPoints == 2)
    {
        type = "Point";
        return type;
    }
    else if (numberOfPoints == 4)
    {
        type = "Line";
        return type;
    }
    else if (numberOfPoints == 6)
    {
        type = "Triangle";
        return type;
    }
    else if (numberOfPoints > 6)
    {
        type = "Polygon";
        return type;
    }

    return type;
}

bool Polygon::isConvex(int numberOfPoints, bool shapeIsConvex)
{

    shapeIsConvex = false;

    double dx1, dy1, dx2, dy2, crproduct;

    //All polygons with 4 points (8 numbers) are convex, it would take atleast 5 points to make it intersect for example
    //All triangles are convex
    if (numberOfPoints == 8 || numberOfPoints == 6)
        return true;

    //In a polygon, all interior angles has to be less than 180 degrees in order for it to be convex.
    for (int i = 0; i < (numberOfPoints / 2); i++)
    {
        dx1 = points[(i + 2) % (numberOfPoints / 2)].x - points[(i + 1) % (numberOfPoints / 2)].x;
        dy1 = points[(i + 2) % (numberOfPoints / 2)].y - points[(i + 1) % (numberOfPoints / 2)].y;

        dx2 = points[i].x - points[(i + 1) % (numberOfPoints / 2)].x;
        dy2 = points[i].y - points[(i + 1) % (numberOfPoints / 2)].y;

        crproduct = (dx1 * dy2) - (dy1 * dx2);

        if (i == 0)
        {
            shapeIsConvex = crproduct > 0;
        }
        else if (shapeIsConvex != (crproduct > 0))
        {
            return false;
        }
    }

    return true;

    area(numberOfPoints, shapeIsConvex);

    //Had to add a third return in order to make the area function call work
    bool convex = true;
    return true;
}

// Source: https://stackoverflow.com/questions/471962/how-do-i-efficiently-determine-if-a-polygon-is-convex-non-convex-or-complex

double Polygon::area(int numberOfPoints, bool isConv)
{

    double areaOfPolygon = 0.0;

    if (isConvex(numberOfPoints, isConv))
    {
        // Im using the shoelace formula for calculating the polygon area
        int j = (numberOfPoints / 2) - 1;

        for (int i = 0; i < (numberOfPoints / 2); i++)
        {
            areaOfPolygon += (points[j].x + points[i].x) * (points[j].y - points[i].y);
            j = i; // j is previous vertex to i
        }

        areaOfPolygon = fabs(areaOfPolygon / 2);

        areaOfPolygon = areaOfPolygon * pow(10, 3);
        areaOfPolygon = floor(areaOfPolygon);
        areaOfPolygon = areaOfPolygon / pow(10, 3);

        return areaOfPolygon;
    }

    else
    {
        areaOfPolygon = -1;
        std::cout << "\nArea: " << areaOfPolygon;
        return areaOfPolygon;
    }
}

//Source: https://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/

double Polygon::circumference(int numberOfPoints)
{

    double centroid = 0, dx, dy;

    for (int i = 0; i < (numberOfPoints / 2); i++)
    {
        dx = points[(i + 1) % (numberOfPoints / 2)].x - points[i].x;
        dy = points[(i + 1) % (numberOfPoints / 2)].y - points[i].y;
        centroid += sqrt(dx * dx + dy * dy);
    }

    //Circumference with a precision of 3 decimal digits
    centroid = centroid * pow(10, 3);
    centroid = floor(centroid);
    centroid = centroid / pow(10, 3);

    return centroid;
}

double *Polygon::position(int numberOfPoints)
{

    double *centroid = new double[2];
    centroid[0] = 0;
    centroid[1] = 0;

    for (int i = 0; i < (numberOfPoints / 2); i++)
    {
        centroid[0] = centroid[0] + points[i].x;
        centroid[1] = centroid[1] + points[i].y;
    }

    centroid[0] = centroid[0] / (numberOfPoints / 2);
    centroid[1] = centroid[1] / (numberOfPoints / 2);

    centroid[0] = centroid[0] * pow(10, 3);
    centroid[0] = floor(centroid[0]);
    centroid[0] = centroid[0] / pow(10, 3);

    centroid[1] = centroid[1] * pow(10, 3);
    centroid[1] = floor(centroid[1]);
    centroid[1] = centroid[1] / pow(10, 3);

    std::cout << "\nCentroid: "
              << "(" << centroid[0] << ", " << centroid[1] << ")";

    distance(numberOfPoints, centroid);

    delete[] centroid;

    centroid = nullptr;

    return centroid;
}

double Polygon::distance(int numberOfPoints, double *centerPoint)
{

    double x1, x2, y1, y2;
    double distanceX, distanceY, distance;

    x1 = centerPoint[0];
    y1 = centerPoint[1];

    //Since distance is part of A2 and it is only focusing on one shape, I chose to compare the centroid to another point far away from the centroid
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

    delete[] centerPoint;
    centerPoint = nullptr;

    return distance;
}

Polygon::~Polygon()
{
    delete[] points;
    points = nullptr;
}