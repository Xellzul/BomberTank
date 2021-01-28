/**
 * @file tile_crate.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Tile Crate class
 * @date 2020-06-06
 */
#ifndef TILE_CRATE_H
#define TILE_CRATE_H

#include "../tile.hpp"
#include "../i_damageable.hpp"

/**
 * @brief Tile Crate is destructable object that drops bonus
 */
class TileCrate : public Tile, public IDamageable
{
public:
    TileCrate();
    virtual ~TileCrate();

    Texture GetTextureId() const override;
    bool AllowCollision(const IPhysical &object) const override;
    void Update(const GameContext &context) override;
    void Damage(const GameContext &context, float amount, DamageType type) override;

private:
    float health_ = 1.0f;
};

#endif