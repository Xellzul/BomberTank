/**
 * @file entity_ammo.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Entity Ammo class
 * @date 2020-06-06
 */
#ifndef ENTITY_AMMO_H
#define ENTITY_AMMO_H

#include "../entity_bonus.hpp"

/**
 * @brief EntityAmmo gives tank faster reload time
 * EntityAmmo destroys itself on collision with tank
 * then it gives tank faster reload time
 */
class EntityAmmo : public EntityBonus
{
public:
    /**
     * @brief Construct a new Entity Ammo object
     */
    EntityAmmo();
    /**
     * @brief Destroy the Entity Ammo object
     */
    virtual ~EntityAmmo();

    Texture GetTextureId() const override;
    void Collide(const GameContext &context, IPhysical &object) override;

private:
    //after this time remove this object from game
    size_t lifeTime_ = 60 * 20; //20 sec
};

#endif