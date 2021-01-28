/**
 * @file entity_ammo.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Entity Ammo class
 * @date 2020-06-06
 */
#include "entity_ammo.hpp"
#include "../world.hpp"

EntityAmmo::EntityAmmo() = default;
EntityAmmo::~EntityAmmo() = default;

Texture EntityAmmo::GetTextureId() const
{
    return Texture::Ammo;
}

void EntityAmmo::Collide(const GameContext &context, IPhysical &object)
{
    Tank *tank = dynamic_cast<Tank *>(&object);
    if (tank)
    {
        tank->ReduceAmmoReloadTime(10);
        context.GetWorld()->DeleteEntity(this);
    }
}
