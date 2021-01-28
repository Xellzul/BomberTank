/**
 * @file entity_speed.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Entity Speed class
 * @date 2020-06-06
 */
#ifndef ENTITY_SPEED_H
#define ENTITY_SPEED_H

#include "../entity_bonus.hpp"

/**
 * @brief EntitySpeed increases tanks speed
 */
class EntitySpeed : public EntityBonus
{
public:
    /**
     * @brief Construct a new Entity Speed object
     */
    EntitySpeed();
    /**
     * @brief Destroy the Entity Speed object
     */
    virtual ~EntitySpeed();

    Texture GetTextureId() const override;
    void Collide(const GameContext &context, IPhysical &object) override;

private:
    //after this time remove this object from game
    size_t lifeTime_ = 60 * 20; //20 sec
};

#endif