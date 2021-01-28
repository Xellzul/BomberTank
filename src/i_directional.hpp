/**
 * @file i_directional.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Directional interface
 * @date 2020-06-07
 */
#ifndef IDIRECTIONAL_H
#define IDIRECTIONAL_H

#include "point_2d.hpp"
#include "e_direction.hpp"
#include "game_context.hpp"

#include <vector>

/**
 * @brief Directional interface
 * gives ability to have direction
 */
class IDirectional
{
public:
    /**
     * @brief Construct a new IDirectional object
     * @param d Direction the object will be facing
     */
    IDirectional(Direction d);
    /**
     * @brief Destroy the IDirectional object
     */
    virtual ~IDirectional();
    /**
     * @brief Set the Direction of object
     * @param d is new Direction
     */
    void SetDirection(Direction d);
    /**
     * @brief Get the Direction of object
     * @return Direction 
     */
    Direction GetDirection() const;
    /**
     * @brief Gets Direction in form of Unit Point
     * adding result of this method will move point in givven direction
     * @return Point2D Directional unit point
     */
    Point2D GetDirectionPoint() const;

    /**
     * @brief Get All possible directions
     * @return std::vector<Direction> 
     */
    static std::vector<Direction> GetAllDirections();
    /**
     * @brief Get All possible directions in random order
     * @param context GameContext
     * @return std::vector<Direction> 
     */
    static std::vector<Direction> GetAllDirectionsShuffled(const GameContext &context);

protected:
    /**
     * @brief Direction of object
     */
    Direction Direction_ = Direction::None;
};
#endif