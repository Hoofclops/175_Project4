//
//  Vector2.h
//  Source
//
//  Created by Brandon Nguyen on 10/28/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#ifndef Vector2_h
#define Vector2_h

class Vector2
{
public:
    float mX;
    float mY;
    
    Vector2();
    Vector2(float x, float y);
    void Add(Vector2 other);
    void Subtract(Vector2 other);
    void Multiply(Vector2 other);
    
};
#endif /* Vector2_h */
