#include "Vector2.h"



Vector2::Vector2()
    :x(0.0f),
    y(0.0f)
{
}


Vector2::~Vector2()
{
}

Vector2::Vector2(float x, float y)
    :x(x),
    y(y)
{

}
Vector2& Vector2::operator*(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}
Vector2& Vector2::operator+=(const Vector2& right)
{
    x += right.x;
    y += right.y;
    return *this;
}
Vector2& Vector2::operator-=(const Vector2& right)
{
    x -= right.x;
    y -= right.y;
    return *this;
}