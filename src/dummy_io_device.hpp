/**
 * @file dummy_io_device.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Dummy IO Device class
 * @date 2020-06-07
 */
#ifndef DUMMY_IO_DEVICE_H
#define DUMMY_IO_DEVICE_H

#include <vector>

#include "io_device.hpp"

/**
 * @brief Dummy io device, does nothing
 */
class DummyIODevice : public IODevice
{
public:
    /**
     * @brief Construct a new Dummy IO Device object
     */
    DummyIODevice();
    /**
     * @brief Destroy the Dummy IO Device object
     */
    virtual ~DummyIODevice();
    void OnWorldSizeChange(const World &world) override;
    void Render(const World &world, const GameContext &context) override;
    std::vector<InputEvent> GetInputEvents() override;
private:
    //bool quit_ = false;
};

#endif