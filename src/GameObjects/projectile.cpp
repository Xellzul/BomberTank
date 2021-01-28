/**
 * @file projectile.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Projectile class
 * @date 2020-06-06
 */
#include "projectile.hpp"

#include "explosion.hpp"
#include "../tank_game.hpp"
#include "../game_context.hpp"

Projectile::Projectile(Direction d, float damage, float speed)
    : IDirectional(d), damage_(damage), speed_(speed), exploded_(false), ignore_(nullptr)
{
    this->SetSize({ProjectileSize, ProjectileSize});
}

Projectile::~Projectile() = default;

Texture Projectile::GetTextureId() const
{
    return Texture::Projectile;
}

bool Projectile::AllowCollision(const IPhysical &object) const
{
    return true;
}

void Projectile::Update(const GameContext &context)
{
    ForceMove(context, GetLocation() + GetDirectionPoint() * speed_);
}

void Projectile::Collide(const GameContext &context, IPhysical &object)
{
    if (exploded_)
        return;

    if (&object == this)
        return;

    if (!object.AllowCollision(*this) && ignore_ != &object)
    {
        exploded_ = true;
        IDamageable *dam = dynamic_cast<IDamageable *>(&object);
        if (dam)
            dam->Damage(context, damage_, DamageType::Kinetic);

        context.GetWorld()->DeleteEntity(this);

        auto explosion = new Explosion(GetSize() * 2);
        explosion->CenterBy(GetMiddle());

        context.GetWorld()->SpawnEntity(explosion);
    }
}

void Projectile::SetIgnoreEntity(const IPhysical *e)
{
    ignore_ = e;
}