//
//  GraphicsAlgorithm.h
//  Project1
//
//  Created by Brandon Nguyen on 9/27/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__GraphicsAlgorithm__
#define __Project1__GraphicsAlgorithm__

#include "Line.h"
#include "Renderer.h"
#include "Polygon.h"

class GraphicsAlgorithm
{
public:
    static void LineDDA(Line line, Color color);
    static Vector3 FindPolyCentroid(Polygon poly);
};

#endif /* defined(__Project1__GraphicsAlgorithm__) */
