//
//  ObjectEditor.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#include "ObjectEditor.h"

ObjectEditor* ObjectEditor::sInstance;
deque<Polygon> ObjectEditor::sPolyList;
deque<Line> ObjectEditor::sLineList;
int ObjectEditor::sSelectedPoly;

ObjectEditor::ObjectEditor()
{
    sSelectedPoly = -1;
}

void ObjectEditor::CreatePolygon(deque<Vector2i> vertPositions)
{
    Polygon poly = Polygon(vertPositions);
    sPolyList.push_back(poly);
}

void ObjectEditor::CreateLine(Line line)
{
    sLineList.push_back(line);
}

deque<Polygon> ObjectEditor::GetPolygons()
{
    return sPolyList;
}

deque<Line> ObjectEditor::GetLines()
{
    return sLineList;
}

void ObjectEditor::CycleSelectedPoly(bool forward)
{
    //Handle first selection
    if(sSelectedPoly == -1)
    {
        if(sPolyList.size() == 0)
            return;
        
        sSelectedPoly = 0;
        sPolyList[sSelectedPoly].SetSelected(true);
        return;
    }
    
    if(forward)
    {
        sPolyList[sSelectedPoly].SetSelected(false);
        unsigned int selectedUnsigned = sSelectedPoly;
        if(selectedUnsigned != sPolyList.size() - 1)
        {
            sSelectedPoly++;
        }
        else
        {
            sSelectedPoly = 0;
        }
        sPolyList[sSelectedPoly].SetSelected(true);
    }
    else
    {
        sPolyList[sSelectedPoly].SetSelected(false);
        if(sSelectedPoly != 0)
        {
            sSelectedPoly--;
        }
        else
        {
            sSelectedPoly = (int)(sPolyList.size() - 1);
        }
        sPolyList[sSelectedPoly].SetSelected(true);

    }
}

void ObjectEditor::ClearData()
{
    sPolyList.clear();
    sLineList.clear();
    sSelectedPoly = -1;
}