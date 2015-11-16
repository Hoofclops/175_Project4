//
//  GraphicsAlgorithm.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/27/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "GraphicsAlgorithm.h"

/**************************
 *ALGORITHM IMPLEMENTATION*
 **************************/

void GraphicsAlgorithm::LineDDA(Line line, Color color)
{
    Renderer *renderer = Renderer::Instance();
    Point a = line.A(), b = line.B();
    
    int dx = b.Position().mX - a.Position().mX,
    dy = b.Position().mY - a.Position().mY, steps;
    float xIncrement, yIncrement, x = a.Position().mX, y = a.Position().mY;
    
    //determine which direction steps will orient towards
    if(fabs(dx) > fabs(dy))
    {
        steps = fabs(dx);
    }
    else
    {
        steps = fabs(dy);
    }
    
    //initialize increments
    xIncrement = (float)dx / (float)steps;
    yIncrement = (float)dy / (float)steps;
    
    //draw first point
    Point p = Point(nearbyint(x), nearbyint(y), color);
    renderer->DrawPoint(p);
    
    //draw each subsequent point, incrementing along the way
    for(int i = 0; i < steps; i++)
    {
        x += xIncrement;
        y += yIncrement;
        
        p = Point(nearbyint(x), nearbyint(y), color);
        renderer->DrawPoint(p);
    }
}


Vector3 GraphicsAlgorithm::FindPolyCentroid(Polygon poly)
{
    deque<Point> vertices = poly.GetVertices();
    Vector3 centroid;
    
    //Find average of all vertices
    long vertexCount = vertices.size();
    for(int i = 0; i < vertexCount; i++)
    {
        centroid.mX += vertices[i].X();
        centroid.mY += vertices[i].Y();
    }
    centroid = centroid.Divide((float)vertexCount);
    return centroid;
}