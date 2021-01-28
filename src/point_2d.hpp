/**
 * @file point_2d.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Point 2D struct
 * @date 2020-06-07
 */
#ifndef POINT_2D_H
#define POINT_2D_H

#include "e_direction.hpp"

/**
 * @brief Point2D is two dimensional vector
 */
struct Point2D
{
    /**
     * @brief Construct a new null Point 2D object
     * value will be [0,0]
     */
    Point2D();
    /**
     * @brief Construct a new unit Point 2D object from Direction
     * @param dir is the Direction the point will be pointing to
     */
    Point2D(Direction dir);

    /**
     * @brief Construct a new Point 2D object
     * @param xv is the x Axis or width
     * @param yv is the y Axis or height
     */
    Point2D(float xv, float yv);

    /**
     * @brief Creates Point and adds values Pointwise
     * @param point to add values to this
     * @return Point2D 
     */
    Point2D operator+(const Point2D &point) const;
    /**
     * @brief Adds Point pointwise to this one
     * @param point to add
     * @return Point2D 
     */
    Point2D &operator+=(const Point2D &point);
    /**
     * @brief Creates Point and subtracts values Pointwise
     * @param point to subtract
     * @return Point2D 
     */
    Point2D operator-(const Point2D &point) const;
    /**
     * @brief Creates Point and subtracts values Pointwise
     * @param point to subtract
     * @return Point2D 
     */
    Point2D &operator-=(const Point2D &point);
    /**
     * @brief Creates Point and divides values
     * @param val to divide by
     * @return Point2D 
     */
    Point2D operator/(float val) const;
    /**
     * @brief Creates Point and multiplies values
     * @param val to multiply by
     * @return Point2D 
     */
    Point2D operator*(float val) const;
    /**
     * @brief Creates Point and multiplies values pointwise
     * @param point to multiply by 
     * @return Point2D 
     */
    Point2D operator*(Point2D &point) const;

    /**
     * @brief Creates Point with absolute values
     * @return Point2D 
     */
    Point2D abs() const;
    /**
     * @brief Creates Point with switched Axis
     * @return Point2D 
     */
    Point2D swap() const;

    /**
     * @brief Returns biggest number in this point
     * @return float is the biggest number
     */
    float max() const;

    /**
     * @brief Calculates euclidean distance between points
     * @param point to calculate distance to
     * @return float is the distance
     */
    float dist(Point2D &point) const;

    /**
     * @brief Calculates euclidean distance between points
     * @param point to calculate distance to
     * @return float is the distance
     */
    float dist(Point2D &&point) const;
    
    /**
     * @brief contains x axis of point or width
     */
    float x = 0;
    /**
     * @brief contains y axis of point or height
     */
    float y = 0;
};

#endif