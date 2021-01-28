/**
 * @file point_2d.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Point 2D struct
 * @date 2020-06-07
 */
#include "point_2d.hpp"
#include "math.h"
#include <algorithm>

Point2D::Point2D(Direction dir) : x(0), y(0)
{
    switch (dir)
    {
    case Direction::Left:
        x = -1;
        break;
    case Direction::Right:
        x = 1;
        break;
    case Direction::Up:
        y = -1;
        break;
    case Direction::Down:
        y = 1;
        break;
    default:
        break;
    }
}

Point2D::Point2D() : x(0), y(0)
{
}

Point2D::Point2D(float xv, float yv) : x(xv), y(yv)
{
}

Point2D Point2D::operator+(const Point2D &point) const
{
    return Point2D(point.x + x, point.y + y);
}

Point2D &Point2D::operator-=(const Point2D &point)
{
    x -= point.x;
    y -= point.y;
    return *this;
}
Point2D &Point2D::operator+=(const Point2D &point)
{
    x += point.x;
    y += point.y;
    return *this;
}
Point2D Point2D::operator/(float val) const
{

    return Point2D(x / val, y / val);
}

Point2D Point2D::operator*(float val) const
{
    return Point2D(x * val, y * val);
}

Point2D Point2D::operator-(const Point2D &point) const
{
    return Point2D(x - point.x, y - point.y);
}

Point2D Point2D::operator*(Point2D &point) const
{
    return Point2D(point.x * x, point.y * y);
}

Point2D Point2D::abs() const
{
    return Point2D(std::fabs(x), std::fabs(y));
}

Point2D Point2D::swap() const
{
    return Point2D(y, x);
}

float Point2D::dist(Point2D &&point) const
{
    return dist(point);
}

float Point2D::dist(Point2D &point) const
{
    return std::sqrt(
        std::pow(x - point.x, 2) +
        std::pow(y - point.y, 2));
}

float Point2D::max() const
{
    return std::max(x, y);
}
