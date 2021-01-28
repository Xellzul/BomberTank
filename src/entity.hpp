/**
 * @file entity.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Entity class
 * @date 2020-06-07
 */
#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.hpp"
#include "i_physical.hpp"

/**
 * @brief Entity is object that is not bound to world grid
 * Can move freely and can be rendered
 */
class Entity : public GameObject, public IPhysical
{
public:
    /**
     * @brief Construct a new Entity object
     */
    Entity();
    /**
     * @brief Destroy the Entity object
     */
    virtual ~Entity();
};

#endif