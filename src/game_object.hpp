/**
 * @file game_object.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of GameObject class
 * @date 2020-06-06
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "game_context.hpp"

/**
 * @brief Every game class must be derivered from GameObject
 */
class GameObject
{
public:
    /**
     * @brief Construct a new Game Object object
     */
    GameObject();

    /**
     * @brief Destroy the Game Object object
     */
    virtual ~GameObject();

    /**
     * @brief Update GameObject
     * This method is called by `World` once a tick
     * @param context Game Context for current game
     */
    virtual void Update(const GameContext &context) = 0;
};

#endif