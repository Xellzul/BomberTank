/**
 * @file entity_bonus.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Entity Bonus class
 * @date 2020-06-06
 */
#ifndef ENTITY_BONUS_H
#define ENTITY_BONUS_H

#include "entity.hpp"

/**
 * @brief EntityBonus is base for all Tank bonuses
 * AI tank will try to collect this
 * has limited lifetime
 */
class EntityBonus : public Entity
{
public:
    /**
     * @brief Destroy the Entity Bonus object
     */
    virtual ~EntityBonus();

    /**
     * @brief Construct a new Entity Bonus object
     */
    EntityBonus();

    void Update(const GameContext &context) override;
    bool AllowCollision(const IPhysical &object) const override;

    /**
     * @brief Get new random Bonus, or no bonus if unlucky (returns nullptr)
     * @param context Game Context
     * @return EntityBonus* new Bonus, can return nullptr
     */
    static EntityBonus *GetBonus(const GameContext &context);

private:
    //after this time remove this object from game
    size_t lifeTime_ = 60 * 20; //20 sec
};

#endif