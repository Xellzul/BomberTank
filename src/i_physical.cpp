/**
 * @file i_physical.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Physical Interface
 * @date 2020-06-07
 */
#include "i_physical.hpp"
#include "world.hpp"

#include <algorithm>

IPhysical::IPhysical()
    : size_({1, 1}), location_({0, 0})
{
}

IPhysical::IPhysical(Point2D size, Point2D location)
    : size_(size), location_(location)
{
}

IPhysical::~IPhysical() = default;

Point2D IPhysical::GetSize() const
{
    return size_;
}

Point2D IPhysical::GetLocation() const
{
    return location_;
}

void IPhysical::SetSize(Point2D newSize)
{
    size_ = newSize;
}
void IPhysical::CenterBy(Point2D newMiddle)
{
    SetLocation(newMiddle - (GetSize() / 2));
}

void IPhysical::SetLocation(Point2D newLocation)
{
    location_ = newLocation;
}

bool IPhysical::Intersects(Point2D pos, Point2D size) const
{
    return (
        ((pos.x + size.x >= location_.x) &&
         (pos.x <= location_.x + size_.x)) &&
        ((pos.y + size.y >= location_.y) &&
         (pos.y <= location_.y + size_.y)));
}

void IPhysical::Collide(const GameContext &context, IPhysical &obj)
{
}

Point2D IPhysical::GetMiddle() const
{
    return location_ + (size_ / 2.0f);
}

bool IPhysical::Move(const GameContext &context, Point2D newLocation)
{
    auto collisions = context.GetWorld()->GetCollisions(newLocation, size_);
    bool willMove = true;
    for (IPhysical *obj : collisions)
    {
        if (obj == this)
            continue;

        if (!obj->AllowCollision(*this))
            willMove = false;

        Collide(context, *obj);
        obj->Collide(context, *this);
    }
    if (willMove)
    {
        location_ = newLocation;
        return true;
    }
    return false;
}

void IPhysical::ForceMove(const GameContext &context, Point2D newLocation)
{
    location_ = newLocation;
}

IPhysical *IPhysical::RayCast(const GameContext &context, Direction direction, const IPhysical *ignore) const
{
    return RayCast(context, direction, size_.max(), ignore);
}

IPhysical *IPhysical::RayCast(const GameContext &context, Direction direction, float size, const IPhysical *ignore) const
{
    Point2D size2d(size, size);
    Point2D loc(GetMiddle() - (size2d / 2));
    Point2D dir(direction);

    float stepSize = size/2;

    int worldSize = std::max(context.GetWorld()->GetWidth(), context.GetWorld()->GetHeigth());

    for (float i = 0; i < worldSize / stepSize; i += stepSize)
    {
        loc += dir * stepSize;
        auto collisisons = context.GetWorld()->GetCollisions(loc, size2d);
        for (IPhysical *p : collisisons)
        {
            if (p == this || p == ignore)
                continue;

            if (!p->AllowCollision(*this))
                return p;
        }
    }

    return nullptr;
}