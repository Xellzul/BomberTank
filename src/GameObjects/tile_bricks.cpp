/**
 * @file tile_bricks.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Tile Bricks class
 * @date 2020-06-06
 */
#include "tile_bricks.hpp"
#include "tile_air.hpp"
#include "../world.hpp"

TileBricks::TileBricks() = default;
TileBricks::~TileBricks() = default;

Texture TileBricks::GetTextureId() const
{
    return Texture::Bricks;
}

bool TileBricks::AllowCollision(const IPhysical &boject) const
{
    return false;
}

void TileBricks::Update(const GameContext &context) {}

void TileBricks::Damage(const GameContext &context, float amount, DamageType type)
{
    //ignore Explosion damage
    if (type == DamageType::Explosion)
        return;

    health_ -= amount;
    if (health_ <= 0)
    {
        //replace me with new tile
        TileAir *newTile = new TileAir();
        newTile->SetLocation(GetLocation());
        context.GetWorld()->ChangeTile(newTile);
    }
}