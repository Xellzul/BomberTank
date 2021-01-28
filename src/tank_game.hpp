/**
 * @file tank_game.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Tank Game class
 * @date 2020-06-09
 */
#ifndef TANK_GAME_H
#define TANK_GAME_H

#include "io_device.hpp"
#include "world.hpp"
#include "game_context.hpp"

/**
 * @brief Tank Game class manages score, connects game with IO and performs game ticks
 * There can run multiple instances of this class
 */
class TankGame
{
public:
    /**
     * @brief Construct a new Tank Game object
     * @param ioDevice device for input and output operations
     * @param debug debug mode
     */
    TankGame(IODevice *ioDevice, bool debug = false);
    /**
     * @brief Destroy the Tank Game object
     */
    ~TankGame();

    /**
     * @brief Loads game from map and then stars it
     * This is blocking call and returns once game is finnished
     * @param mapName location of map file
     * @param secondPlayer if there are 2 players
     */
    void StartGame(std::string &mapName, bool secondPlayer);

    /**
     * @brief Get the World object
     * @return World& 
     */
    World &GetWorld() const;

    /**
     * @brief Get current game tick
     * first tick = 0
     * @return size_t tick
     */
    size_t GetTick() const;

    /**
     * @brief Prints text if game is set to debug mode
     * @param text to print
     * @return const TankGame& itself 
     */
    const TankGame &printDebug(const std::string &text) const;

    /**
     * @brief Tells game player died
     */
    void OnPlayerDeath();

    /**
     * @brief Asks game if its is singleplayer game
     * @return true is single player
     * @return false is game of two players
     */
    bool isSinglePlayer() const;
    /**
     * @brief Get Score of player
     * works only in single player mode
     * @return int score
     */
    int GetScore() const;

    /**
     * @brief whether game should continou next tick
     */
    bool run_ = false;
    /**
     * @brief whether game was force ended
     * eg by user
     */
    bool force_end_ = false;

private:
    /**
     * @brief Actual Game loop
     * ticks 60 times a second
     */
    void Run();
    /**
     * @brief Converts input even into action
     * @param e input event
     */
    void HandleInput(InputEvent e);

    /**
     * @brief writes best score to file
     * @param map map file name
     * @param score to write
     * @return true if writing was succesful
     * @return false if writing was unsuccesful
    */
    bool WriteScore(std::string &map, int score);
    
    /**
     * @brief Reads best score associated with map
     * returns -1 if no score yet or operation was unsuccesful
     * @param map Map File name
     * @return int score
     */
    int ReadScore(std::string &map);

    //game of two players
    bool vsPlayer_ = false;

    //was ended ahead of time
    bool debug_ = false;
    int score_ = 0;

    size_t tick_ = 0;
    GameContext context_;

    World *world_ = nullptr;
    IODevice *iodevice_ = nullptr;

    //name of map that is in use
    std::string mapName_;
};

#endif
