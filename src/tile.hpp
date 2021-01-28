/**
 * @file tile.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Tile abstrac class
 * @date 2020-06-09
 */
#ifndef TILE_H
#define TILE_H

#include "game_object.hpp"
#include "i_physical.hpp"

/**
 * @brief Tile, base class for all static objects
 * This class should not be moved
 */
class Tile : public GameObject, public IPhysical
{
public:
    /**
     * @brief Construct a new Tile object
     */
    Tile();
    /**
     * @brief Destroy the Tile object
     */
    virtual ~Tile() = default;
};

#endif