/**
 * @file entity_bonus.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Entity Bonus class
 * @date 2020-06-06
 */
#include "entity_bonus.hpp"
#include "world.hpp"
#include "GameObjects/entity_ammo.hpp"
#include "GameObjects/entity_max_health.hpp"
#include "GameObjects/entity_speed.hpp"
#include "GameObjects/entity_repair.hpp"

EntityBonus *EntityBonus::GetBonus(const GameContext &context)
{
    auto weights = {
        1,  //no bonus
        1,  //Ammo
        1,  //health
        1,  //speed
        2   //repair
    };

    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    int rand = dist(*context.GetRandom());

    switch (rand)
    {
    case 0:
        return nullptr;
    case 1:
        return new EntityAmmo();
    case 2:
        return new EntityMaxHealth();
    case 3:
        return new EntitySpeed();
    case 4:
        return new EntityRepair();
    }

    throw;
}

EntityBonus::EntityBonus() = default;
EntityBonus::~EntityBonus() = default;

bool EntityBonus::AllowCollision(const IPhysical &object) const
{
    //allow anything but tank so we get Collide callback
    if (dynamic_cast<const Tank *>(&object))
        return false;
    return true;
}

void EntityBonus::Update(const GameContext &context)
{
    --lifeTime_;
    if (lifeTime_ == 0)
    {
        context.GetWorld()->DeleteEntity(this);
    }
}
