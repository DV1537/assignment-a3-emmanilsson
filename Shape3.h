#include <iostream>

#ifndef SHAPE3_H
#define SHAPE3_H

#include "Vector3.h"


using namespace std;


class Shape{


    private: 
            Vector2f *points;
            int numberOfPoints;
        
    public:
        

        virtual std::string getType();

        virtual double area();

        virtual double circumference();

        virtual double* position();
        
        virtual bool isConvex();


};



#endif // !SHAPE3_H