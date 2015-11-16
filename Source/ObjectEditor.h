//
//  ObjectEditor.h
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__ObjectEditor__
#define __Project1__ObjectEditor__

#include <deque>
//#include <math.h>
//#include <exception>
//#include <iostream>
#include "Polygon.h"
//#include "Line.h"
//#include "Renderer.h"
//#include "Vector2i.h"
//#include "Vector3.h"
//#include "Matrix.h"
class ObjectEditor
{
private:
    static ObjectEditor* sInstance;
    static deque<Polygon> sPolyList;
    static deque<Line> sLineList;
    static int sSelectedPoly;
    
    ObjectEditor();
public:
    static ObjectEditor *Instance()
    {
        if (!sInstance)
            sInstance = new ObjectEditor;
        return sInstance;
    }
    
    void CreatePolygon(deque<Vector2i> vertPositions);
    void CreateLine(Line line);
    
    deque<Polygon> GetPolygons();
    deque<Line> GetLines();
        
    void CycleSelectedPoly(bool forward);
    void ClearData();
};
#endif /* defined(__Project1__ObjectEditor__) */
