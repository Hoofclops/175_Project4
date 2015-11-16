//
//  Triangle.cpp
//  Source
//
//  Created by Brandon Nguyen on 10/28/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(){}

Triangle::Triangle(Point3d a, Point3d b, Point3d c)
{
    mA.point = a;
    mB.point = b;
    mC.point = c;
}

deque<Point3d> Triangle::GetVertices()
{
    deque<Point3d> ret;
    ret.push_back(mA.point);
    ret.push_back(mB.point);
    ret.push_back(mC.point);
    
    return ret;
}

deque<Line> Triangle::GetEdges2d(deque<Vector2> vects, Triangle tri)
{
    deque<Line> ret;
    
    if(vects.size() != 3)
    {
        throw invalid_argument("Not enough vectors");
    }
    
    Point p1 = Point((int)(vects[0].mX), (int)(vects[0].mY), tri.A()->point.GetColor());
    Point p2 = Point((int)(vects[1].mX), (int)(vects[1].mY), tri.B()->point.GetColor());
    Point p3 = Point((int)(vects[2].mX), (int)(vects[2].mY), tri.C()->point.GetColor());

    ret.push_back(Line(p1,p2));
    ret.push_back(Line(p2,p3));
    ret.push_back(Line(p3,p1));

    return ret;
}

float Triangle::GetSumX()
{
    return mA.point.X() + mB.point.X() + mC.point.X();
}

float Triangle::GetSumY()
{
    return mA.point.Y() + mB.point.Y() + mC.point.Y();
}

float Triangle::GetSumZ()
{
    return mA.point.Z() + mB.point.Z() + mC.point.Z();
}
