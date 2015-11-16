//
//  InputOutputUtility.cpp
//  Project1
//
//  Created by Brandon Nguyen on 9/28/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//
//  Parse polygon file Code based off of code from http://cs.dvc.edu/HowTo_Cparse.html

#include "InputOutputUtility.h"

void InputOutputUtility::QueryWindowSize()
{
    int xDim, yDim;
    
    cout << "Enter X window dimension: ";
    cin >> xDim;
    cout << "Enter Y window dimension: ";
    cin >> yDim;
    cin.ignore();
    
    Renderer::Instance()->InitWindow(xDim + 1, yDim + 1);
}

void InputOutputUtility::DetectInput(unsigned char key, int xmouse, int ymouse)
{
    switch(key)
    {
            case 'i':
                ProcessInput();
            break;
            case 'I':
                ProcessInput();
            break;
            case 'n':
                ObjectEditor::Instance()->CycleSelectedPoly(true);
            break;
            case 'b':
                ObjectEditor::Instance()->CycleSelectedPoly(false);
            break;
    }
    
    Renderer::Instance()->DrawScene();
}

void InputOutputUtility::ProcessInput()
{
    string input;
    cout << "Enter command: ";
    getline(cin, input);
    
    deque<string> tokens = SplitString(input, string(" "));
    
    if(tokens.size() == 0)
    {
        return;
    }
    
    string command = tokens[0];
    tokens.pop_front();
    
    //Parse strings
    if(command == "Load" || command == "load")
    {
        ProcessCommandLoadFile(tokens);
    }
    else if(command == "Save" || command == "save")
    {
        ProcessCommandSaveFile(tokens);
    }
    else if(command == "Set" || command == "set")
    {
        ProcessCommandSet(tokens);
    }
    else if(command == "Clear" || command == "clear")
    {
        Renderer::Instance()->ClearBuffer();
        ObjectEditor::Instance()->ClearData();
    }
    else
    {
        cout << "Invalid command, please enter another command" << endl;
        return;
    }
}


void InputOutputUtility::ProcessCommandLoadFile(deque<string> tokens)
{
    if(tokens.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    ParsePolygonFile(tokens[0]);
}

void InputOutputUtility::ProcessCommandSaveFile(deque<string> tokens)
{
    if(tokens.size() != 1)
    {
        cout << "Invalid command" << endl;
        return;
    }
    
    SavePolygonFile(tokens[0]);
}

void InputOutputUtility::ProcessCommandSet(deque<string> tokens)
{
    string token = tokens.front();
    tokens.pop_front();
    
}

void InputOutputUtility::ParsePolygonFile(string fileName)
{
    ifstream fin;
    
#ifdef __APPLE__
    fin.open("//Users//BrandonHome//GitHub//175_Project4//DataFiles//" + fileName);
#else
    fin.open(fileName);
#endif

    if (!fin.good())
        throw runtime_error("Error opening poly.txt");
    
    const char* tokens[MAX_TOKENS] = {}; // initialize to 0
    deque<Vector2i> vertexPositions;
    
    while (!fin.eof())
    {
        char buf[MAX_LINE_LEN];
        fin.getline(buf, MAX_LINE_LEN);
        
        int i = 0;
        tokens[0] = strtok(buf, ", ");
        if (tokens[0]) // zero if line is blank
        {
            for (i = 1; i < MAX_TOKENS; i++)
            {
                tokens[i] = strtok(0, ", ");
                if (!tokens[i])
                    break;
            }
        }
        
        if(!tokens[0])
        {
            continue;
        }
        
        //Parse strings
        if(strcmp(tokens[0], "End") == 0 || strcmp(tokens[0], "end") == 0)
        {
            ObjectEditor::Instance()->CreatePolygon(vertexPositions);
            vertexPositions.clear();
        }
        else
        {
            float x = atof(tokens[0]);
            float y = atof(tokens[1]);
            vertexPositions.push_back(Vector2i(x, y));
        }
    }
    
    fin.close();
}

void InputOutputUtility::SavePolygonFile(string fileName)
{
    ofstream fout;
    
    
#ifdef __APPLE__
    fout.open("//Users//BrandonHome//GitHub//175_Project4//DataFiles//" + fileName, ofstream::out | ofstream::trunc);
#else
    fout.open(fileName, ofstream::out | ofstream::trunc);
#endif
    
    deque<Polygon> allPolys = ObjectEditor::Instance()->GetPolygons();
    
    long polyCount = allPolys.size();
    for(unsigned int i = 0; i < polyCount; i++)
    {
        deque<Point> vertices = allPolys[i].GetVertices();
        
        //store vertices
        long vertexCount = vertices.size();
        for(unsigned int j = 0; j < vertexCount; j++)
        {
            fout << vertices[j].X() << " " << vertices[j].Y() << " " << "\n";
        }
        
        fout << "End" << "\n" << "\n";
    }
    
    fout.close();
}

deque<string> InputOutputUtility::SplitString(string s, string delims)
{
    deque<string> tokens;
    const char *str = s.c_str();
    do
    {
        const char *begin = str;
        
        while(*str)//(*str != c && *str)
        {
            
            //Search delims for current char
            size_t found = delims.find(*str);
            if (found != string::npos)
                break;
            
            str++;
        }
        
        string tok = string(begin, str);
        if(tok != "")
            tokens.push_back(string(begin, str));
        
    } while (0 != *str++);
    
    return tokens;

}

deque<Vector3> InputOutputUtility::ExtractVertices(deque<string> tokens)
{
    deque<Vector3> vertexPositions;
    
    long n = tokens.size();
    for(int i = 0; i < n; i++)
    {
        deque<string> vertex = SplitString(tokens[i], string("(),"));
        
        if(vertex.size() != 3)
        {
            cout << "Invalid vertex format" << endl;
            vertexPositions.clear();
            exit(1);
        }
        
        Vector3 vertPos = Vector3(atof(vertex[0].c_str()), atof(vertex[1].c_str()), atof(vertex[2].c_str()));
        vertexPositions.push_back(Vector3(vertPos.mX, vertPos.mY, vertPos.mZ));
    }
    
    return vertexPositions;
}
