/**
 * @file i_directional.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Directional interface
 * @date 2020-06-07
 */
#include "i_directional.hpp"
#include <algorithm>

IDirectional::IDirectional(Direction d = Direction::None)
    : Direction_(d)
{
}

void IDirectional::SetDirection(Direction d)
{
    Direction_ = d;
}

IDirectional::~IDirectional() = default;

Direction IDirectional::GetDirection() const
{
    return Direction_;
}

Point2D IDirectional::GetDirectionPoint() const
{
    return Point2D(Direction_);
}

std::vector<Direction> IDirectional::GetAllDirections()
{
    return {Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right};
}

std::vector<Direction> IDirectional::GetAllDirectionsShuffled(
    const GameContext &context)
{
    auto allDirections = GetAllDirections();
    
    std::shuffle(allDirections.begin(),
                 allDirections.end(),
                 (*context.GetRandom()));

    return allDirections;
}