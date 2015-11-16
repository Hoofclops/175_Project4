//
//  Triangle.h
//  Source
//
//  Created by Brandon Nguyen on 10/28/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h

#include <deque>
#include <exception>
#include <limits>
#include "Line.h"
#include "Point3d.h"
#include "Vector2.h"

struct TriVert
{
    Point3d point;
    Vector3 normal;
};

class Triangle
{
private:
    TriVert mA, mB, mC;
    bool mSelected;
public:
    
    Triangle();
    Triangle(Point3d a, Point3d b, Point3d c);
    TriVert* A(){return &mA;}
    TriVert* B(){return &mB;}
    TriVert* C(){return &mC;}
    
    deque<Point3d> GetVertices();
    static deque<Line> GetEdges2d(deque<Vector2> vects, Triangle tri);
    float GetSumX();
    float GetSumY();
    float GetSumZ();
    
    bool Selected(){return mSelected;}
    void Selected(bool b){mSelected = b;};    
};
#endif /* Triangle_h */
