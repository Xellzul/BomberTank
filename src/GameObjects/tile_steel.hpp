/**
 * @file tile_steel.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Tile Steel class
 * @date 2020-06-06
 */
#ifndef TILE_STEEL_H
#define TILE_STEEL_H

#include "../tile.hpp"

/**
 * @brief Tile Steel is used as impassable block
 */
class TileSteel : public Tile
{
public:
    /**
     * @brief Construct a new Tile Steel object
     */
    TileSteel();
    /**
     * @brief Destroy the Tile Steel object
     */
    virtual ~TileSteel();

    Texture GetTextureId() const override;
    bool AllowCollision(const IPhysical &object) const override;
    void Update(const GameContext &context) override;
};

#endif