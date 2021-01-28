/**
 * @file i_damageable.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of IDamageable interface and DamageType enum
 * @date 2020-06-06
 */
#ifndef IDAMAGEABLE_H
#define IDAMAGEABLE_H

#include "game_context.hpp"

/**
 * @enum DamageType
 * @brief Contains all possible damage types
 */
enum class DamageType
{
    None,
    Kinetic,
    Explosion
};

/**
 * @interface IDamageable
 * @brief interface for classes that are able to be damaged
 */
class IDamageable
{
public:
    /**
     * @brief Construct a new IDamageable object
     */
    IDamageable();
    /**
     * @brief Destroy the IDamageable object
     */
    virtual ~IDamageable();

    /**
     * @brief This applies damage to the object
     * @param context gameContext reference
     * @param amount amount of damage
     * @param type type of damage
     */
    virtual void Damage(const GameContext &context, float amount, DamageType type) = 0;
};

#endif