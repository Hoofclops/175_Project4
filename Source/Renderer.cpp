//
//  Renderer.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "Renderer.h"

/****************************
 *STATIC VARIABLE DECLARATIONS*
 ****************************/

Renderer* Renderer::sInstance;
Vector2i Renderer::sScreenSize;
float*  Renderer::sPixelBuffer;
int Renderer::sMainWindow;
deque<function<void()>> Renderer::sAnimationQueue;
bool Renderer::sDisplayControlPolygon;

/****************************
 *PUBLIC FUNCTIONS*
 ****************************/

void Renderer::InitWindow(int xDim, int yDim)
{
    sScreenSize = Vector2i(xDim, yDim);
    int windowPixelCount = (sScreenSize.mX) * (sScreenSize.mY) * 3;
    
    sPixelBuffer = new float[windowPixelCount];
    
    for(int i = 0; i < windowPixelCount; i++)
    {
        sPixelBuffer[i] = 0.0f;
    }
}

void Renderer::DrawScene()
{
    ClearBuffer();
    
    deque<Polygon> controlPolys = ObjectEditor::Instance()->GetPolygons();
    
    //Determine limits
    int min = INT_MAX, max = 0;
    for(Polygon &poly : controlPolys)
    {
        UpdateLimits(&min, &max, poly);
    }
    
    //Draw Curves
    for(Polygon poly : controlPolys)
    {
        //normalize points
        deque<Point> controlPoints = NormalizeVertices(poly.GetVertices(), min, max);
        poly.SetVertices(controlPoints);
        //draw bezier curve
        DrawCurve(poly);
    }
    
    //Post redisplay for all sub windows
    glutSetWindow(sMainWindow);
    glutPostRedisplay();
}

void Renderer::DrawPoint(Point point)
{
    int pixelStart = PosToIndex((point.Position()));
    
    Color color = point.GetColor();
    
    if(pixelStart >= 0 && pixelStart + 2 <= (sScreenSize.mX) * (sScreenSize.mY) * 3)
    {
        sPixelBuffer[pixelStart] = color.GetRed();
        sPixelBuffer[pixelStart + 1] = color.GetGreen();
        sPixelBuffer[pixelStart + 2] = color.GetBlue();
    }
    else
    {
        throw out_of_range("Point outside of pixel buffer range");
    }
}

void Renderer::DrawPoint(Point point, Color color)
{
    int pixelStart = PosToIndex((point.Position()));
    
    if(pixelStart >= 0 && pixelStart + 2 <= (sScreenSize.mX) * (sScreenSize.mY) * 3)
    {
        sPixelBuffer[pixelStart] = color.GetRed();
        sPixelBuffer[pixelStart + 1] = color.GetGreen();
        sPixelBuffer[pixelStart + 2] = color.GetBlue();
    }
    else
    {
        throw out_of_range("Point outside of pixel buffer range");
    }
}

void Renderer::DisplayPixelBuffer()
{
    //Misc.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();//load identity matrix
    
    //draws pixel on screen, width and height must match pixel buffer dimension
    glDrawPixels(sScreenSize.mX, sScreenSize.mY, GL_RGB, GL_FLOAT, sPixelBuffer);
    glEnd();
    glFlush();
}

void Renderer::IdleAnimation()
{
    long n = sAnimationQueue.size();
    if(n != 0)
    {
        sAnimationQueue.front()();
        sAnimationQueue.pop_front();
        Renderer::Instance()->DrawScene();
    }
    
}

void Renderer::ClearBuffer()
{
    int n = sScreenSize.mX * sScreenSize.mY * 3;
    for(int i = 0; i < n; i++)
    {
        sPixelBuffer[i] = 0.0f;
    }
}

/****************************
 *PRIVATE FUNCTIONS*
 ****************************/
Renderer::Renderer()
{
    sDisplayControlPolygon = true;
}

void Renderer::DrawCurve(Polygon controlPoly)
{
    deque<Line> edges = controlPoly.GetEdges();
    
    for(Line edge : edges)
    {
        GraphicsAlgorithm::LineDDA(edge, Color::White());
    }
}

int Renderer::PosToIndex(Vector2i pos)
{
    int width = sScreenSize.mX;
    return (pos.mX + width * pos.mY) * 3;
}

void Renderer::UpdateLimits(int* min, int* max, Polygon poly)
{
    deque<Point> vertices = poly.GetVertices();
    for(Point &vert : vertices)
    {
        int x = vert.X(), y = vert.Y();
        if(x < *min)
            *min = x;
        if(y < *min)
            *min = y;
        if(x > *max)
            *max = x;
        if(y > *max)
            *max = y;
    }
}

deque<Point> Renderer::NormalizeVertices(deque<Point> vertices, int min, int max)
{
    deque<Point> normalized;
    float fMin = (float)min, fMax = (float)max;
    
    long n = vertices.size();
    //Find normalized points
    for(int i = 0; i < n; i++)
    {
        float x = vertices[i].X(), y = vertices[i].Y();
        
        float diff = fMax - fMin;
        if(diff == 0)
        {
            throw exception();
        }
        
        x = (x - fMin) / (fMax - fMin);
        y = (y - fMin) / (fMax - fMin);
        
        if(x < 0 || x > 1 || y < 0 || y > 1)
        {
            throw exception();
        }
        
        int pX = x * sScreenSize.mX, pY = y * sScreenSize.mY;
        normalized.push_back(Point(pX, pY));
    }
    
    return normalized;
}