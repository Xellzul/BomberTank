/**
 * @file tile_bricks.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Tile Bricks class
 * @date 2020-06-06
 */
#ifndef TILE_BRICKS_H
#define TILE_BRICKS_H

#include "../tile.hpp"
#include "../i_damageable.hpp"

/**
 * @brief Tile Bricks is used as destructable object
 */
class TileBricks : public Tile, public IDamageable
{
public:
    /**
     * @brief Construct a new Tile Bricks object
     */
    TileBricks();
    /**
     * @brief Destroy the Tile Bricks object
     */
    virtual ~TileBricks();

    Texture GetTextureId() const override;
    bool AllowCollision(const IPhysical &object) const override;
    void Update(const GameContext &context) override;
    void Damage(const GameContext& context, float amount, DamageType type) override;
private:
    //remaining health of the bricks
    float health_ = 1.0f;
};

#endif