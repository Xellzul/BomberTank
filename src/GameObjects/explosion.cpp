/**
 * @file explosion.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Explosion class
 * @date 2020-06-06
 */
#include "explosion.hpp"
#include "../i_damageable.hpp"
#include "../world.hpp"

Explosion::Explosion(Point2D explosionSize) : lifeTime_(15)
{
    SetSize(explosionSize);
}

Explosion::~Explosion() = default;

Texture Explosion::GetTextureId() const
{
    switch (lifeTime_ / 4)
    {
    case 0:
        return Texture::Explosion1;
    case 1:
        return Texture::Explosion2;
    case 2:
        return Texture::Explosion3;
    case 3:
        return Texture::Explosion4;
    default:
        return Texture::Error;
    }
}

void Explosion::Collide(const GameContext &context, IPhysical &object)
{
    IDamageable *damageable = dynamic_cast<IDamageable *>(&object);
    if (damageable)
        damageable->Damage(context, DamagePerTick, DamageType::Explosion);
}

bool Explosion::AllowCollision(const IPhysical &object) const
{
    return true;
}

void Explosion::Update(const GameContext &context)
{
    lifeTime_--;
    if (lifeTime_ == 0)
        context.GetWorld()->DeleteEntity(this);
}