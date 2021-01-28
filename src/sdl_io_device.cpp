/**
 * @file sdl_io_device.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of SDL IO Device class
 * @date 2020-06-07
 */
#include "sdl_io_device.hpp"
#include <algorithm>
#include <stdexcept>

SDLIODevice::SDLIODevice(size_t resolution)
    : texturepack_(nullptr), width_(800), height_(600), resolution_(resolution)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) 
        throw std::runtime_error("Cannot initialize SDL");

    IMG_Init(IMG_INIT_PNG) ;

    window_ = SDL_CreateWindow("Tanks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    SDL_RenderPresent(renderer_);
}

SDLIODevice::~SDLIODevice()
{
    delete texturepack_;
    texturepack_ = nullptr;

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    IMG_Quit();
    SDL_Quit();
}

void SDLIODevice::LoadTextures(const std::string &assetFolder, bool debugMode = false)
{
    delete texturepack_;
    texturepack_ = new TexturePack(renderer_, assetFolder, debugMode);
}

void SDLIODevice::OnWorldSizeChange(const World &world)
{
    width_ = resolution_ * world.GetWidth();
    height_ = resolution_ * world.GetHeigth();

    SDL_SetWindowSize(window_, width_, height_);
}

void SDLIODevice::Render(const World &world, const GameContext &context)
{
    SDL_Rect pos;
    pos.h = resolution_;
    pos.w = resolution_;
    pos.x = 0;
    pos.y = 0;
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    for (size_t x = 0; x < world.GetWidth(); x++)
    {
        for (size_t y = 0; y < world.GetHeigth(); y++)
        {
            pos.x = x * resolution_;
            pos.y = y * resolution_;

            SDL_RenderCopy(renderer_, texturepack_->GetTexture(world.GetBlock(x, y)->GetTextureId()), NULL, &pos);
        }
    }

    for (const Entity *e : world.GetEntities())
        RenderEntity(e);

    SDL_RenderPresent(renderer_);
}

void SDLIODevice::RenderEntity(const Entity *e)
{
    SDL_Rect pos;
    pos.h = resolution_ * e->GetSize().y;
    pos.w = resolution_ * e->GetSize().x;
    pos.x = resolution_ * e->GetLocation().x;
    pos.y = resolution_ * e->GetLocation().y;
    SDL_RenderCopy(renderer_, texturepack_->GetTexture(e->GetTextureId()), NULL, &pos);

    const Tank *tank = dynamic_cast<const Tank *>(e);
    if (tank)
    {
        //it is tank, render Health Bar here
        SDL_Rect healthPos;
        healthPos.h = resolution_ * .2f;
        healthPos.w = resolution_ * tank->GetSize().y;
        healthPos.x = resolution_ * tank->GetLocation().x;
        healthPos.y = resolution_ * (.1f + tank->GetLocation().y + tank->GetSize().y);

        SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer_, &healthPos);

        healthPos.w =
            resolution_ *
            tank->GetSize().y *
            (tank->GetHealth() / tank->GetMaxHealth());

        SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer_, &healthPos);
    }
}

std::vector<InputEvent> SDLIODevice::GetInputEvents()
{
    std::vector<InputEvent> toReturn;
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_WINDOWEVENT:
            HandleWindowEvent(e, toReturn);
            break;

        case SDL_QUIT:
            toReturn.emplace_back(InputEvent::Quit);
            break;

        case SDL_KEYDOWN:
            HandleKeyPressEvent(e, toReturn);
            break;

        case SDL_KEYUP:
            break;

        default:
            break;
        }
    }
    return toReturn;
}

void SDLIODevice::HandleWindowEvent(SDL_Event &e, std::vector<InputEvent> &queue) const
{
    switch (e.window.event)
    {
    case SDL_WINDOWEVENT_CLOSE:
        queue.emplace_back(InputEvent::Quit);
        return;
    }
}

void SDLIODevice::HandleKeyPressEvent(SDL_Event &e, std::vector<InputEvent> &queue) const
{
    switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
        queue.emplace_back(InputEvent::Player1Left);
        return;
    case SDLK_UP:
        queue.emplace_back(InputEvent::Player1Up);
        return;
    case SDLK_RIGHT:
        queue.emplace_back(InputEvent::Player1Right);
        return;
    case SDLK_DOWN:
        queue.emplace_back(InputEvent::Player1Down);
        return;
    case SDLK_SPACE:
        queue.emplace_back(InputEvent::Player1Fire);
        return;

    case SDLK_a:
        queue.emplace_back(InputEvent::Player2Left);
        return;
    case SDLK_w:
        queue.emplace_back(InputEvent::Player2Up);
        return;
    case SDLK_d:
        queue.emplace_back(InputEvent::Player2Right);
        return;
    case SDLK_s:
        queue.emplace_back(InputEvent::Player2Down);
        return;
    case SDLK_x:
        queue.emplace_back(InputEvent::Player2Fire);
        return;
    }
}