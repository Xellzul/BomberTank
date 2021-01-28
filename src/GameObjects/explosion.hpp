/**
 * @file explosion.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Explosion class
 * @date 2020-06-06
 */
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "../entity.hpp"

/**
 * @brief Explosion damages everything nearby
 */
class Explosion : public Entity
{
public:
    /**
     * @brief Construct a new Explosion object
     * @param explosionSize how big the explosion will be
     */
    Explosion(Point2D explosionSize);
    /**
     * @brief Destroy the Explosion object
     */
    ~Explosion();

    Texture GetTextureId() const override;
    void Update(const GameContext &context) override;
    bool AllowCollision(const IPhysical &object) const override;
    void Collide(const GameContext &context, IPhysical &object) override;

    /**
     * @brief constant, how much will Explosion damage nearby objects per tick
     */
    static constexpr float DamagePerTick = 0.005f;

private:
    size_t lifeTime_;
};

#endif