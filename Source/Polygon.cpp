//
//  Polygon.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Polygon.h"

Polygon::Polygon(deque<Vector2i> vertPositions)
{
    long n = vertPositions.size();
    if(n <= 0)
    {
        throw invalid_argument("Invalid amount of vertices passed to Polygon constructor");
    }
    
    //Construct vertices
    Point first = Point(vertPositions[0]);
    mVertices.push_back(first);
    for(int i = 1; i < n; i++)
    {
        Point p = Point(vertPositions[i]);
        mVertices.push_back(p);
    }

    mSelected = false;
}


void Polygon::AddEdgeConnection(Vector2i vect, deque<Vector2i>* ret)
{
    bool alreadyAdded = false;
    long m = ret->size();
    for(int j = 0; j < m; j++)
    {
        if((ret->at(j).mX == vect.mX && ret->at(j).mY == vect.mY) || (ret->at(j).mX == vect.mY && ret->at(j).mY == vect.mX))
        {
            alreadyAdded = true;
            break;
        }
    }
    if(!alreadyAdded) ret->push_back(vect);
}

deque<Point> Polygon::GetVertices()
{    
    return mVertices;
}
void Polygon::SetVertex(int index, Vector3 pos)
{
    mVertices[index].X(pos.mX);
    mVertices[index].Y(pos.mY);
}

void Polygon::SetVertices(deque<Point> verts)
{
    mVertices = verts;
}

deque<Line> Polygon::GetEdges()
{
    deque<Line> edges;
    
    long n = mVertices.size() - 1;
    for(int i = 0; i < n; i++)
    {
        Line l = Line(mVertices[i], mVertices[i+1]);
        edges.push_back(l);
    }
    return edges;
}

void Polygon::SetSelected(bool isSelected)
{
    mSelected = isSelected;
}

bool Polygon::IsSelected()
{
    return mSelected;
}
