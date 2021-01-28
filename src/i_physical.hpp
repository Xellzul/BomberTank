/**
 * @file i_physical.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Physical Interface
 * @date 2020-06-07
 */
#ifndef IPHYSICAL_H
#define IPHYSICAL_H

#include "game_object.hpp"
#include "point_2d.hpp"
#include "texture_pack.hpp"
#include "game_context.hpp"
#include "e_direction.hpp"

/**
 * @brief IPhysical represents any object that can interact with physics
 * IPhysical is represented rectangle
 */
class IPhysical
{
public:
    /**
     * @brief Construct a new IPhysical object
     */
    IPhysical();
    /**
     * @brief Construct a new IPhysical object
     * @param size_ is size of object
     * @param location_ is where the object will be (top left corner of rectangle)
     */
    IPhysical(Point2D size_, Point2D location_);
    /**
     * @brief Destroy the IPhysical object
     */
    virtual ~IPhysical();

    /**
     * @brief Get Texture Id of this object
     * @return Texture 
     */
    virtual Texture GetTextureId() const = 0;
    /**
     * @brief Tells if other object allows collision with parameter, it is not enforced
     * @param object Gamecontext
     * @return true if collision is allowed
     * @return false if collision is not allowed
     */
    virtual bool AllowCollision(const IPhysical &object) const = 0;
    /**
     * @brief Asks object what to do when colided with other object
     * @param context Game Context
     * @param object it colided to
     */
    virtual void Collide(const GameContext &context, IPhysical &object);
    /**
     * @brief Tries to move object, asks other objects if it can move into
     * invokes Collide even if move was uncusseful on both objects
     * @param context Game Context
     * @param newLocation location to go to
     * @return true if move was succesful
     * @return false if move was not succesful, location didnt change
     */
    bool Move(const GameContext &context, Point2D newLocation);
    /**
     * @brief Moves to new location, doesnt ask if can move, doesnt invoke Collide
     * @param context Game Context
     * @param newLocation location to go to
     */
    void ForceMove(const GameContext &context, Point2D newLocation);
    /**
     * @brief checks for for collision between this object and rectangle
     * doesnt invoke Collide method
     * @param pos position of rectangle (top-left point)
     * @param size size of rectangle
     * @return true if rectangle and object collides
     * @return false if there is no collision
     */
    bool Intersects(Point2D pos, Point2D size) const;
    /**
     * @brief Get the Size of object
     * @return Point2D 
     */
    Point2D GetSize() const;
    /**
     * @brief Get the Location point of object
     * @return Point2D 
     */
    Point2D GetLocation() const;
    /**
     * @brief Get the Middle point of object
     * @return Point2D 
     */
    Point2D GetMiddle() const;
    /**
     * @brief changes location so it is centered by point 
     * @param newMiddle where new center will be
     */
    void CenterBy(Point2D newMiddle);
    /**
     * @brief changes size point of object
     * @param newSize 
     */
    void SetSize(Point2D newSize);
    /**
     * @brief changes location point of object
     * @param newLocation 
     */
    void SetLocation(Point2D newLocation);

    /**
     * @brief Casts ray in givven direction
     * ignores object that casts the ray and object in parameter ignore
     * @param context GameContext
     * @param direction of ray cast
     * @param size width of the raycast
     * @param ignore object that will be ignored
     * @return IPhysical* null if not hit anything, otherwise pointer hitted object
     */
    IPhysical *RayCast(const GameContext &context, Direction direction, float size, const IPhysical *ignore = nullptr) const;
    
    /**
     * @brief Casts ray in givven direction
     * ignores object that casts the ray and object in parameter ignore
     * width of raycast will be same as object casting it
     * @param context GameContext
     * @param direction of ray cast
     * @param ignore object that will be ignored
     * @return IPhysical* null if not hit anything, otherwise pointer hitted object
     */
    IPhysical *RayCast(const GameContext &context, Direction direction, const IPhysical *ignore = nullptr) const;

private:
    Point2D size_;
    Point2D location_;
};

#endif