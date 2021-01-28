/**
 * @file tile_air.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Tile Air class
 * @date 2020-06-06
 */
#include "tile_air.hpp"

TileAir::TileAir() = default;
TileAir::~TileAir() = default;

Texture TileAir::GetTextureId() const
{
    return Texture::Air;
}

bool TileAir::AllowCollision(const IPhysical &object) const
{
    return true;
}

void TileAir::Update(const GameContext &context)
{
}