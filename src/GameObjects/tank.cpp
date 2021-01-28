/**
 * @file tank.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Tank class
 * @date 2020-06-07
 */
#include "tank.hpp"

#include "../tank_game.hpp"
#include "../world.hpp"
#include "../game_context.hpp"

#include "projectile.hpp"
#include "explosion.hpp"

Tank::Tank() : IDirectional(Direction::Up)
{
    this->SetSize({TankSize, TankSize});
}

Tank::~Tank() = default;

void Tank::Damage(const GameContext &context, float amount, DamageType type)
{
    health_ -= amount;
    if (health_ <= 0)
    {
        context.GetWorld()->DeleteEntity(this);

        auto explosion = new Explosion(GetSize() * 5);
        explosion->CenterBy(GetMiddle());

        context.GetWorld()->SpawnEntity(explosion);
    }
}

Texture Tank::GetTextureId() const
{
    switch (Direction_)
    {
    case Direction::Up:
        return Texture::TankUp;
    case Direction::Down:
        return Texture::TankDown;
    case Direction::Left:
        return Texture::TankLeft;
    case Direction::Right:
        return Texture::TankRight;
    default:
        return Texture::Error;
    }
}

bool Tank::AllowCollision(const IPhysical &object) const
{
    return false;
}

void Tank::Update(const GameContext &context)
{
    Move(context, GetLocation() + GetDirectionPoint() * speed_);
}

bool Tank::CanFire(const GameContext &context) const
{
    return (canFireTick_ <= context.GetTankGame()->GetTick());
}

void Tank::Fire(const GameContext &context)
{
    if (!CanFire(context))
        return;

    canFireTick_ = context.GetTankGame()->GetTick() + fireDelayTicks_;
    Projectile *p = new Projectile(Direction_, projectileDamage_, projectileSpeed_);

    p->SetIgnoreEntity(this);
    p->CenterBy(GetMiddle());

    context.GetWorld()->SpawnEntity(p);
}

float Tank::GetHealth() const
{
    return health_;
}

float Tank::GetMaxHealth() const
{
    return maxHealth_;
}

void Tank::ReduceAmmoReloadTime(size_t ticks)
{
    fireDelayTicks_ = std::max<size_t>(fireDelayTicks_ - ticks, 10);
}

void Tank::Repair(float health)
{
    health_ = std::min(health_ + health, maxHealth_);
}

void Tank::AddHealth(float health)
{
    maxHealth_ += health;
    health_ += health;
}

void Tank::AddSpeed(float speed)
{
    speed_ = std::min(speed_ + speed, 0.2f);
}