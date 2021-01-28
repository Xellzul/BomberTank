/**
 * @file game_context.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of GameContext class
 * @date 2020-06-06
 */
#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <random>

class TankGame;
class World;

/**
 * @brief Containts context for game
 * this is passed to all Game Objects
 */
class GameContext
{
public:
    /**
     * @brief Construct a new Game Context object
     */
    GameContext();
    /**
     * @brief Destroy the Game Context object
     */
    ~GameContext();

    /**
     * @brief Get the World object
     * @return World* 
     */
    World *GetWorld() const;
    /**
     * @brief Set the World object
     * @param world 
     */
    void SetWorld(World *world);

    /**
     * @brief Get the Tank Game, this is EntryPoint for game
     * @return TankGame* 
     */
    TankGame *GetTankGame() const;
    /**
     * @brief Set the Tank Game object
     * @param tankGame 
     */
    void SetTankGame(TankGame *tankGame);

    /**
     * @brief Get the Random object
     * Use this for generating Random Numbers
     * @return std::mt19937*
     */
    std::mt19937 *GetRandom() const;
    /**
     * @brief Set the Random object
     * random generator will be freed by destructor of this class
     * @param random Random Generator to set
     */
    void SetRandom(std::mt19937 *random);

private:
    World *world_ = nullptr;
    TankGame *tankGame_ = nullptr;
    std::mt19937 *random_ = nullptr;
};

#endif