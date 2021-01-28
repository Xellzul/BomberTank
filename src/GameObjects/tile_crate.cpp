/**
 * @file tile_crate.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Tile Air class
 * @date 2020-06-06
 */
#include "tile_crate.hpp"
#include "tile_air.hpp"
#include "../entity_bonus.hpp"
#include "../world.hpp"

TileCrate::TileCrate() = default;
TileCrate::~TileCrate() = default;

Texture TileCrate::GetTextureId() const
{
    return Texture::Crate;
}

bool TileCrate::AllowCollision(const IPhysical &object) const
{
    return false;
}

void TileCrate::Update(const GameContext &context)
{
}

void TileCrate::Damage(const GameContext &context, float amount, DamageType type)
{
    if (type == DamageType::Explosion)
        return;

    health_ -= amount;
    if (health_ <= 0)
    {
        TileAir *newTile = new TileAir();
        newTile->SetLocation(GetLocation());
        context.GetWorld()->ChangeTile(newTile);

        EntityBonus *bonus = EntityBonus::GetBonus(context);
        if (!bonus)
            return;

        bonus->SetLocation(GetLocation());

        context.GetWorld()->SpawnEntity(bonus);
    }
}