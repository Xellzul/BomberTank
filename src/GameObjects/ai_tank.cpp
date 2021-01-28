/**
 * @file ai_tank.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of AI Tank class
 * @date 2020-06-07
 */
#include "ai_tank.hpp"
#include "../tank_game.hpp"
#include "../entity_bonus.hpp"

#include "projectile.hpp"
#include "tile_crate.hpp"
#include "tile_bricks.hpp"

#include <random>
#include <algorithm>

AITank::~AITank() = default;
AITank::AITank() = default;

bool AITank::CanGoDirection(const GameContext &context, Direction dir) const
{
    IPhysical *tar = RayCast(context, dir, GetSize().max());

    if (!tar)
        return true;

    if (tar->GetMiddle().dist(GetMiddle()) > 2.0f)
        return true;

    return false;
}

int AITank::CalculateFireWeight(const GameContext &context, Direction dir) const
{
    if (!CanFire(context))
        return 0;

    int weight = 0;

    //create dummy projectile for RayCast
    Projectile p(Direction_, 0, 0);
    p.SetIgnoreEntity(this);
    p.CenterBy(GetMiddle());

    IPhysical *target = p.RayCast(context, dir, this);

    if (dynamic_cast<Tank *>(target))
        weight += 200;
    else if (dynamic_cast<TileCrate *>(target))
        weight += 20;
    else if (dynamic_cast<TileBricks *>(target))
        weight += 5;

    if (target && target->GetMiddle().dist(GetMiddle()) < 2.0f)
        weight /= 5;

    return weight;
}

int AITank::CalculateMovementWeight(const GameContext &context, Direction dir) const
{
    int weight = 1;
    IPhysical *target = RayCast(context, dir);

    if (dynamic_cast<EntityBonus *>(target))
        weight += 70;

    if (CanGoDirection(context, dir))
        weight += 30;

    if (dir == Direction_)
        weight *= 5;

    return weight;
}

void AITank::UpdateAI(const GameContext &context)
{
    auto aiWeights = {
        /* FireUp    */
        CalculateFireWeight(context, Direction::Up),
        /* FireDown    */
        CalculateFireWeight(context, Direction::Down),
        /* FireLeft    */
        CalculateFireWeight(context, Direction::Left),
        /* FireRight    */
        CalculateFireWeight(context, Direction::Right),
        /* GoUp     */
        CalculateMovementWeight(context, Direction::Up),
        /* GoDown     */
        CalculateMovementWeight(context, Direction::Down),
        /* GoLeft     */
        CalculateMovementWeight(context, Direction::Left),
        /* GoRight     */
        CalculateMovementWeight(context, Direction::Right)};

    std::discrete_distribution<int> dist(aiWeights.begin(), aiWeights.end());
    int rand = dist(*context.GetRandom());

    switch (rand)
    {
    case 0:
        SetDirection(Direction::Up);
        Fire(context);
        break;
    case 1:
        SetDirection(Direction::Down);
        Fire(context);
        break;
    case 2:
        SetDirection(Direction::Left);
        Fire(context);
        break;
    case 3:
        SetDirection(Direction::Right);
        Fire(context);
        break;
    case 4:
        SetDirection(Direction::Up);
        break;
    case 5:
        SetDirection(Direction::Down);
        break;
    case 6:
        SetDirection(Direction::Left);
        break;
    case 7:
        SetDirection(Direction::Right);
        break;
    }
}

void AITank::Update(const GameContext &context)
{
    if (nextAIUpdate_ <= context.GetTankGame()->GetTick())
    {
        UpdateAI(context);
        nextAIUpdate_ = context.GetTankGame()->GetTick() + 7;
    }

    Tank::Update(context);
}