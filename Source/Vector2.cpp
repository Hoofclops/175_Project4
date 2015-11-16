//
//  Vector2.cpp
//  Source
//
//  Created by Brandon Nguyen on 10/28/15.
//  Copyright © 2015 Brandon Nguyen. All rights reserved.
//

#include "Vector2.h"

Vector2::Vector2()
{
    mX = 0;
    mY = 0;
}

Vector2::Vector2(float x, float y)
{
    mX = x;
    mY = y;
}

void Vector2::Add(Vector2 other)
{
    this->mX += other.mX;
    this->mY += other.mY;
}

void Vector2::Subtract(Vector2 other)
{
    this->mX -= other.mX;
    this->mY -= other.mY;
}

void Vector2::Multiply(Vector2 other)
{
    this->mX *= other.mX;
    this->mY *= other.mY;
}