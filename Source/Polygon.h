//
//  Polygon.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Polygon__
#define __Project1__Polygon__

#include <deque>
#include <list>
#include <stdexcept>
#include <iostream>
#include "Point.h"
#include "Line.h"
#include "Vector3.h"
#include "Vector3i.h"
#include "Vector2i.h"
#include "Vector2.h"

class Polygon
{
private:
    deque<Point> mVertices;
    
    void AddEdgeConnection(Vector2i vect, deque<Vector2i>* ret);
    
    bool mSelected;

public:
    Polygon(deque<Vector2i> vertPositions);
    
    deque<Point> GetVertices();
    void SetVertex(int index, Vector3 pos);
    void SetVertices(deque<Point> verts);

    deque<Line> GetEdges();
    
    void SetSelected(bool isSelected);
    bool IsSelected();
};
#endif /* defined(__Project1__Polygon__) */
