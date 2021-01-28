/**
 * @file sdl_io_device.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of SDL IO Device class
 * @date 2020-06-07
 */
#ifndef SDL_IO_DEVICE_H
#define SDL_IO_DEVICE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

#include "io_device.hpp"
#include "texture_pack.hpp"

/**
 * @brief SDLIODevice is SDL implementation of IODevice
 */
class SDLIODevice : public IODevice
{
public:
    /**
     * @brief Construct a new SDLIODevice object
     * @param resolution valid range is <1, 255>
     */
    SDLIODevice(size_t resolution);
    /**
     * @brief Destroy the SDLIODevice object
     */
    virtual ~SDLIODevice();

    /**
     * @brief Loads textures from disk, can be called multiple times
     * @param assetFolder folder to load textures from
     * @param debugMode writes more debug info
     */
    void LoadTextures(const std::string &assetFolder, bool debugMode);

    void OnWorldSizeChange(const World &world) override;
    void Render(const World &world, const GameContext &context) override;
    std::vector<InputEvent> GetInputEvents() override;

private:
    /**
     * @brief Converts SDL_Event that is Window type to InputEvent and appends to queue
     * @param e what event to convert
     * @param queue where to append the event
     */
    void HandleWindowEvent(SDL_Event &e, std::vector<InputEvent> &queue) const;

    /**
     * @brief Converts SDL_Event that is KeyPress type to InputEvent and appends to queue
     * @param e what event to convert
     * @param queue where to append the event
     */
    void HandleKeyPressEvent(SDL_Event &e, std::vector<InputEvent> &queue) const;

    /**
     * @brief Renders Entity
     * @param e Entity to render
     */
    void RenderEntity(const Entity *e);

    TexturePack *texturepack_;
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    size_t width_;
    size_t height_;
    size_t resolution_;
};

#endif