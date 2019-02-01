#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "Shape3.h"
#include "Point3.h"
#include "Line3.h"
#include "Polygon3.h"
#include "Triangle3.h"
#include "Vector3.h"

using namespace std;

int main(int argc, const char *argv[])
{

    double a, b;
    std::ifstream myfile;
    std::stringstream strStream;
    std::string line;

    int lineNumber = 1;
    int numCoords1 = 0;
    int numCoords2 = 0;

    //Allocate memory for dynamic arrays with the coordinates for the individual shapes

    double *firstShapeX = new double[numCoords1 / 2];
    double *firstShapeY = new double[numCoords1 / 2];

    double *secondShapeX = new double[numCoords2 / 2];
    double *secondShapeY = new double[numCoords2 / 2];

    myfile.open(argv[1]);

    strStream.clear();

    //Read from file and count the amount of coordinates

    while (std::getline(myfile, line))
    {

        strStream << line;

        while (strStream >> a)
        {

            if (lineNumber == 1)
            {
                std::cout << a << " ";
                numCoords1++;
            }

            else if (lineNumber == 2)
            {
                std::cout << a << " ";
                numCoords2++;
            }
        }

        lineNumber++;
        strStream.clear();
    }

    lineNumber = 1;

    if ((numCoords1 + numCoords2) % 2 == 0)
    {
        //The amount of numbers is even
    }
    else
    {
        std::cout << "The amount of numbers is uneven. \n";

        exit(EXIT_FAILURE);
    }

    strStream.str("");
    strStream.clear(); // Clear state flags
    strStream.seekg(0, ios::beg);

    myfile.close();

    myfile.open(argv[1]);

    //Read from file again, storing the coordinates in the dynamic arrays
    while (std::getline(myfile, line))
    {

        strStream << line;

        if (lineNumber == 1)
        {
            for (int i = 0; i < (numCoords1 / 2); i++)
            {
                strStream >> firstShapeX[i];
                strStream >> firstShapeY[i];
            }
        }

        else if (lineNumber == 2)
        {
            for (int i = 0; i < (numCoords2 / 2); i++)
            {
                strStream >> secondShapeX[i];
                strStream >> secondShapeY[i];
            }
        }

        if ((numCoords1 == 0) || (numCoords2 == 0) || !strStream.eof())
        {
            std::cout << "One of the lines is empthy or has input not allowed (whitespace after the last numbers is not allowed). \n";

            exit(EXIT_FAILURE);
        }

        //(E.g you can't create a point by writing one x-coord and one y-coord on separate lines)

        lineNumber++;
        strStream.clear();
    }


    
    for (int i = 0; i < (numCoords1 / 2); i++)
    {
        if(firstShapeX[i] < 0 || firstShapeY[i] < 0)
        {
            std::cout << "Negative numbers are not allowed.";
        }

        exit(EXIT_FAILURE);
    }
    

    for (int i = 0; i < (numCoords2 / 2); i++)
    {
        if(secondShapeX[i] < 0 || secondShapeY[i] < 0)
        {
            std::cout << "Negative numbers are not allowed.";
        }

        exit(EXIT_FAILURE);
    }




    //Create objects of type polygon, one for each shape
    Polygon shape1(firstShapeX, firstShapeY, numCoords1);
    Polygon shape2(secondShapeX, secondShapeY, numCoords2);


    //Create an object for the new shape
    //Functions for overloaded operators = and + is "called"
    Polygon newShape;
    newShape = shape1 + shape2;



    //Release all dynamically allocated memory
    delete[] firstShapeX;
    firstShapeX = NULL;

    delete[] firstShapeY;
    firstShapeY = NULL;

    delete[] secondShapeX;
    secondShapeX = NULL;

    delete[] secondShapeY;
    secondShapeY = NULL;


    return 0;

}
