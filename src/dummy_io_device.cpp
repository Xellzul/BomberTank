/**
 * @file sdl_io_device.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Dummy IO Device class
 * @date 2020-06-07
 */
#include "dummy_io_device.hpp"
#include "tank_game.hpp"

DummyIODevice::DummyIODevice() = default;
DummyIODevice::~DummyIODevice() = default;

void DummyIODevice::OnWorldSizeChange(const World &world)
{
}

void DummyIODevice::Render(const World &world, const GameContext &context)
{
    //if (context.GetTankGame()->GetTick() > 60 * 40)
    //    quit_ = true;
}

std::vector<InputEvent> DummyIODevice::GetInputEvents()
{
    std::vector<InputEvent> toReturn;
    //if (quit_)
    //    toReturn.emplace_back(InputEvent::Quit);

    return toReturn;
}