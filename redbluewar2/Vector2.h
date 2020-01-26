#pragma once
class Vector2
{
public:
    Vector2();
    Vector2(float x, float y);
    ~Vector2();
public:
    Vector2& operator*(float scalar);
    Vector2& operator+=(const Vector2& right);
    Vector2& operator-=(const Vector2& right);
public:
    float x;
    float y;
};

