/**
 * @file entity_speed.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Entity Speed class
 * @date 2020-06-06
 */
#include "entity_speed.hpp"
#include "../world.hpp"

EntitySpeed::EntitySpeed() = default;
EntitySpeed::~EntitySpeed() = default;

Texture EntitySpeed::GetTextureId() const
{
    return Texture::Speed;
}

void EntitySpeed::Collide(const GameContext &context, IPhysical &object)
{
    Tank *tank = dynamic_cast<Tank *>(&object);
    if (tank)
    {
        tank->AddSpeed(0.01f);
        context.GetWorld()->DeleteEntity(this);
    }
}
