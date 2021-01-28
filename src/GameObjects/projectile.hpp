/**
 * @file projectile.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Projectile class
 * @date 2020-06-06
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../entity.hpp"
#include "../i_directional.hpp"

/**
 * @brief Projectile fired by the tanks
 */
class Projectile : public Entity, public IDirectional
{
public:
    /**
     * @brief Construct a new Projectile object
     * @param d direction the projectile will go
     * @param damage the projectile will do on impact
     * @param speed of projectile
     */
    Projectile(Direction d, float damage, float speed);
    /**
     * @brief Destroy the Projectile object
     */
    ~Projectile();
    /**
     * @brief sets object the projectile will ignore and not hit
     * @param object wont be hit be this projectile
     */
    void SetIgnoreEntity(const IPhysical *object);

    Texture GetTextureId() const override;
    void Update(const GameContext &context) override;
    bool AllowCollision(const IPhysical &object) const override;
    void Collide(const GameContext &context, IPhysical &object) override;

    /**
     * @brief constant, by default this is size of projectile
     */
    static constexpr float ProjectileSize = 0.25f;

private:
    float damage_;
    float speed_;
    //did this object hit and exploded allready?
    bool exploded_;
    //object i cant hit
    const IPhysical *ignore_;
};

#endif