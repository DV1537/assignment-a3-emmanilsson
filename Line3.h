#include <iostream>

#ifndef LINE_H
#define LINE_H


#include "Shape3.h"
#include "Vector.h"

class Line: public Shape
{

    private:

        int numberOfPoints;
        Vector2f *points;

    public:
        
        Line(Vector2f* sourcePoints, int numberOfPoints);
        ~Line();

        std::string getType();
        

};



#endif // !LINE_H