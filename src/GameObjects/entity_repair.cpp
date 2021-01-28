/**
 * @file entity_repair.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Entity Repair class
 * @date 2020-06-06
 */
#include "entity_repair.hpp"
#include "../world.hpp"

EntityRepair::EntityRepair() = default;
EntityRepair::~EntityRepair() = default;

Texture EntityRepair::GetTextureId() const
{
    return Texture::Repair;
}

void EntityRepair::Collide(const GameContext &context, IPhysical &object)
{
    Tank *tank = dynamic_cast<Tank *>(&object);
    if (tank)
    {
        tank->Repair(1.0f);
        context.GetWorld()->DeleteEntity(this);
    }
}
