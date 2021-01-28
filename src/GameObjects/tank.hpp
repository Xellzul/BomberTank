/**
 * @file tank.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Tank class
 * @date 2020-06-06
 */
#ifndef TANK_H
#define TANK_H

#include "../entity.hpp"
#include "../i_directional.hpp"
#include "../i_damageable.hpp"

/**
 * @brief Tank is main character in this game
 * tank can be destroyed, can fire, can move in the world
 */
class Tank : public Entity, public IDirectional, public IDamageable
{
public:
    /**
     * @brief Construct a new Tank object
     */
    Tank();
    /**
     * @brief Destroy the Tank object
     */
    virtual ~Tank();

    Texture GetTextureId() const override;
    void Update(const GameContext &context) override;
    bool AllowCollision(const IPhysical &object) const override;

    /**
     * @brief Increases fire rate of Tank
     * @param ticks to decrease realod time
     */
    void ReduceAmmoReloadTime(size_t ticks);

    /**
     * @brief Returns whether Tank can fire
     * @param context Game Context
     * @return true if Fire method will fire new Projectile
     * @return false if Fire method wont do anything
     */
    bool CanFire(const GameContext &context) const;

    /**
     * @brief Tries to Fire new projectile, does nothing if cant fire
     * @param context Game Context
     */
    void Fire(const GameContext &context);

    /**
     * @brief Deals damage to tank
     * if destryoed then destroys the tank itself at end of the tick
     * @param context Game Context
     * @param amount of damage
     * @param type of damage
     */
    void Damage(const GameContext &context, float amount, DamageType type);

    /**
     * @brief Get the current Health of Tank
     * @return float 
     */
    float GetHealth() const;

    /**
     * @brief Get the Max Health of Tank
     * @return float 
     */
    float GetMaxHealth() const;

    /**
     * @brief Adds health to Tank, caps at MaxHealth
     * @param health
     */
    void Repair(float health);

    /**
     * @brief Adds Max health to Tank, also `repairs` the same amount
     * @param health 
     */
    void AddHealth(float health);

    /**
     * @brief Adds Max speed to Tank
     * @param speed 
     */
    void AddSpeed(float speed);

    /**
     * @brief Constant, by default this is size of tank
     */
    static constexpr float TankSize = 1.3f;

private:
    float health_ = 4.0f;
    float maxHealth_ = 4.0f;

    size_t fireDelayTicks_ = 60; // 1 per 60ticks
    size_t canFireTick_ = 0;     // when the tank will be able to fire

    float speed_ = 0.1f; //speed of tank movement

    float projectileSpeed_ = 0.4f;
    float projectileDamage_ = 1.0f;
};

#endif