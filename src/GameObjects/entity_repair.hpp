/**
 * @file entity_repair.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Entity Repair class
 * @date 2020-06-06
 */
#ifndef ENTITY_REPAIR_H
#define ENTITY_REPAIR_H

#include "../entity_bonus.hpp"

/**
 * @brief EntityRepair increases tanks repair
 */
class EntityRepair : public EntityBonus
{
public:
    /**
     * @brief Construct a new Entity Repair object
     */
    EntityRepair();
    /**
     * @brief Destroy the Entity Repair object
     */
    virtual ~EntityRepair();

    Texture GetTextureId() const override;
    void Collide(const GameContext &context, IPhysical &object) override;

private:
    //after this time remove this object from game
    size_t lifeTime_ = 60 * 20; //20 sec
};

#endif