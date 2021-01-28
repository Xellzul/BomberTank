/**
 * @file tile_steel.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Tile Steel class
 * @date 2020-06-06
 */
#include "tile_steel.hpp"

TileSteel::TileSteel() = default;
TileSteel::~TileSteel() = default;

Texture TileSteel::GetTextureId() const
{
    return Texture::Steel;
}

bool TileSteel::AllowCollision(const IPhysical &object) const
{
    return false;
}

void TileSteel::Update(const GameContext &context)
{
}
