#include <iostream>
#include <fstream>
#include <string>

#include "Shape3.h"

using namespace std;


std::string Shape::getType()
{
    std::string type;
    return type;
}

double Shape::area()
{   
    int defaultArea = -1;
    return defaultArea;
}


double Shape::circumference()
{
    int defaultPerimeter = -1;
    return defaultPerimeter; 
}


double *Shape::position()
{
    double *centroid;
    delete centroid;
    centroid = NULL;
    return centroid;
}


bool Shape::isConvex()
{
    std::cout << "\n" << "Convex: - " << "\n";
    return false;
}