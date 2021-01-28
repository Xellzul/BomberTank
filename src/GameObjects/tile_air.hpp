/**
 * @file tile_air.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Tile Air class
 * @date 2020-06-06
 */
#ifndef TILE_AIR_H
#define TILE_AIR_H

#include "../tile.hpp"

/**
 * @brief Tile Air is used as background - Empty tile
 * Everything can pass thru this tile
 */
class TileAir : public Tile
{
public:
    /**
     * @brief Construct a new Tile Air object
     */
    TileAir();
    /**
     * @brief Destroy the Tile Air object
     */
    virtual ~TileAir();

    Texture GetTextureId() const override;
    bool AllowCollision(const IPhysical &object) const override;
    void Update(const GameContext& context) override;
};

#endif