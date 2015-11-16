//
//  main.cpp
//  Project4
//
//  Created by Brandon Nguyen on 9/25/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Renderer.h"
#include "ObjectEditor.h"
#include "InputOutputUtility.h"

int main(int argc, char *argv[])
{

    Renderer::Instance()->InitWindow(600, 600);
    Vector2i screenSize = Renderer::Instance()->ScreenSize();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(screenSize.mX, screenSize.mY);
    glutInitWindowPosition(100, 100);
    
    Renderer::sMainWindow = glutCreateWindow("Project 4");
    glutDisplayFunc(Renderer::DisplayPixelBuffer);
    glutKeyboardFunc(InputOutputUtility::DetectInput);
    
    glutIdleFunc(Renderer::IdleAnimation);
    
    glClearColor(0, 0, 0, 0);

    glutMainLoop();//main display loop, will display until terminate
    
    return 0;
}
