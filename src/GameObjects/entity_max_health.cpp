/**
 * @file entity_max_health.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Entity Max Health class
 * @date 2020-06-06
 */
#include "entity_max_health.hpp"
#include "../world.hpp"

EntityMaxHealth::EntityMaxHealth() = default;
EntityMaxHealth::~EntityMaxHealth() = default;

Texture EntityMaxHealth::GetTextureId() const
{
    return Texture::Health;
}

void EntityMaxHealth::Collide(const GameContext &context, IPhysical &object)
{
    Tank *tank = dynamic_cast<Tank *>(&object);
    if (tank)
    {
        tank->AddHealth(2.0f);
        context.GetWorld()->DeleteEntity(this);
    }
}
