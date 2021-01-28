/**
 * @file entity_max_health.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Entity Max Health class
 * @date 2020-06-06
 */
#ifndef ENTITY_MAX_HEALTH_H
#define ENTITY_MAX_HEALTH_H

#include "../entity_bonus.hpp"

/**
 * @brief EntityMaxHealth increases tanks max health on collection
 * also heals for same amount
 */
class EntityMaxHealth : public EntityBonus
{
public:
    /**
     * @brief Construct a new Entity Max Health object
     */
    EntityMaxHealth();
    /**
     * @brief Destroy the Entity Max Health object
     */
    virtual ~EntityMaxHealth();

    Texture GetTextureId() const override;
    void Collide(const GameContext &context, IPhysical &object) override;

private:
    //after this time remove this object from game
    size_t lifeTime_ = 60 * 20; //20 sec
};

#endif