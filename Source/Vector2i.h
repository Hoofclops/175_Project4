//
//  Vector2i.h
//  Project1
//
//  Created by Brandon Nguyen on 9/26/15.
//  Copyright (c) 2015 Brandon Nguyen. All rights reserved.
//

#ifndef __Project1__Vector2i__
#define __Project1__Vector2i__

class Vector2i
{
public:
    int mX;
    int mY;
    
    Vector2i();
    Vector2i(int x, int y);
    void Add(Vector2i other);
    void Subtract(Vector2i other);
    void Multiply(Vector2i other);
    
    bool operator<(Vector2i const &rhs) const
    {
        return this->mX < rhs.mX || (!(rhs.mX < this->mX) && this->mY < rhs.mY);
    }
    
    bool operator==(Vector2i const &rhs) const
    {
        return this->mX == rhs.mX && this->mY == rhs.mY;
    }

};

//bool operator<(Vector2i const &lhs, Vector2i const &rhs) const
//{
//    return lhs.mX < rhs.mX || (!(rhs.mX < lhs.mX) && lhs.mY < rhs.mY);
//}

#endif /* defined(__Project1__Vector2i__) */
