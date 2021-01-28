/**
 * @file game_context.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of GameContext class
 * @date 2020-06-06
 */

#include "game_context.hpp"

#include "tank_game.hpp"
#include "world.hpp"

GameContext::GameContext() = default;
GameContext::~GameContext()
{
    delete random_;
}

World *GameContext::GetWorld() const { return world_; }
void GameContext::SetWorld(World *world) { world_ = world; }

TankGame *GameContext::GetTankGame() const { return tankGame_; }
void GameContext::SetTankGame(TankGame *tankGame) { tankGame_ = tankGame; }

std::mt19937 *GameContext::GetRandom() const { return random_; }
void GameContext::SetRandom(std::mt19937 *random)
{
    delete random_;
    random_ = random;
}