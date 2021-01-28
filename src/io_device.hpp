/**
 * @file io_device.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of IODevice and InputEvent enum
 * @date 2020-06-06
 */
#ifndef IO_DEVICE_H
#define IO_DEVICE_H

#include <vector>

#include "world.hpp"

/**
 * @enum InputEvent
 * @brief All possible input events
 */
enum class InputEvent
{
    Quit,

    Player1Up,
    Player1Down,
    Player1Left,
    Player1Right,
    Player1Fire,

    Player2Up,
    Player2Down,
    Player2Left,
    Player2Right,
    Player2Fire
};

/**
 * @brief Base class for all IO 
 * Inherit from this class when you are writing new graphics output or input
 */
class IODevice
{
public:
    /**
    * @brief Construct a new IODevice object
    */
    IODevice();
    /**
     * @brief Destroy the IODevice object
     */
    virtual ~IODevice();

    /**
     * @brief This is Called when world dimensions are changed or new world is loaded
     * @param world that is changed
     */
    virtual void OnWorldSizeChange(const World &world) = 0;
    /**
     * @brief Requests Render on screen
     * @param world to render
     * @param context gameContext
     */
    virtual void Render(const World &world, const GameContext &context) = 0;
    /**
     * @brief returns all events that should be processed
     * @return std::vector<InputEvent> events
     */
    virtual std::vector<InputEvent> GetInputEvents() = 0;
};

#endif