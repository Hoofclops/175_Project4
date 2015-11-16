//
//  Renderer.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Renderer__
#define __Project1__Renderer__

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//#include <string>
//#include <deque>
//#include <cmath>
//#include <functional>
//#include <iostream>
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Color.h"
#include "Polygon.h"
#include "GraphicsAlgorithm.h"
#include "ObjectEditor.h"
//#include "Line3d.h"

using namespace std;

//Should contain the pixel buffer and handle drawing of points, lines, and polygons
class Renderer
{
public:
    static int sMainWindow;
    static Vector2i  sScreenSize;
    static std::deque<std::function<void()>> sAnimationQueue;
    
    static Renderer* Instance()
    {
        if (!sInstance)
            sInstance = new Renderer;
        return sInstance;
    }
    
    void InitWindow(int xDim, int yDim);
    
    Vector2i ScreenSize(){return sScreenSize;};
    void ScreenSize(Vector2i size){sScreenSize = size;}
    
    void DrawScene();
    void DrawPoint(Point point);
    void DrawPoint(Point point, Color color);

    static void DisplayPixelBuffer();
    
    static void IdleAnimation();
    
    void ClearBuffer();
    
    void ToggleControlPolygon()
    {
        sDisplayControlPolygon = !sDisplayControlPolygon;
    }
    
private:
    static Renderer* sInstance;
    static float* sPixelBuffer;
    static bool sDisplayControlPolygon;

    Renderer();
    
    void DrawCurve(Polygon controlPoly);
    
    //Convert coordinate position to appropriate array index in pixel buffer
    int PosToIndex(Vector2i pos);
    
    void UpdateLimits(int* min, int* max, Polygon poly);
    deque<Point> NormalizeVertices(deque<Point> vertices, int min, int max);
};

#endif /* defined(__Project1__Renderer__) */
