/**
 * @file texture_pack.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Texture Pack class
 * @date 2020-06-07
 */
#include "texture_pack.hpp"

#include <filesystem>
#include <iostream>

TexturePack::TexturePack(SDL_Renderer *renderer, const std::string &folder, bool debugMode)
    : renderer_(renderer)
{
    textures_ = std::vector<SDL_Texture *>(255, nullptr);
    surfaces_ = std::vector<SDL_Surface *>(255, nullptr);

    if (debugMode)
        std::cout << "Loading Error Texture" << std::endl;

    //load default/error texture
    SDL_RWops *errorMem = SDL_RWFromMem((void *)errorImage, sizeof(errorImage));
    SDL_Surface *errorSurface = IMG_Load_RW(errorMem, 1);
    SDL_Texture *errorTexture = SDL_CreateTextureFromSurface(renderer_, errorSurface);
    textures_[0] = errorTexture;
    surfaces_[0] = errorSurface;

    std::filesystem::directory_entry directiory(folder);
    if (!directiory.is_directory())
    {
        std::cerr << "Cannot load textures from: <" << folder << ">" << std::endl;
        return;
    }
    std::cout << "Loading Texture Pack: " << folder << std::endl;

    //load every texture
    for (const auto &dirEntry : std::filesystem::directory_iterator(folder))
    {
        if (dirEntry.is_directory())
            continue;

        if (debugMode)
            std::cout << "Loading: " << dirEntry << " with id " << dirEntry.path().stem() << std::endl;

        SDL_Surface *surface = IMG_Load(dirEntry.path().c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);

        int num = 0;
        bool loaded = false;
        try
        {
            num = std::stoi(dirEntry.path().stem());
            loaded = true;
        }
        catch (std::exception &e)
        {
            std::cerr << "Cannot load Texture with invalid id: " << dirEntry.path().stem() << std::endl;
        }

        if (num > 255 || num < 0)
        {
            std::cout << "Ignoring texture with id " << num << " must be in range of <1, 255>" << std::endl;
            loaded = false;
        }

        if (!loaded || textures_[num] != nullptr || surfaces_[num] != nullptr) // didnt load, free
        {
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
            continue;
        }

        textures_[num] = texture;
        surfaces_[num] = surface;
    }

    if (debugMode)
        std::cout << "Texture Pack Loaded" << std::endl;
}

TexturePack::~TexturePack()
{
    for (SDL_Surface *v : surfaces_)
        SDL_FreeSurface(v);

    for (SDL_Texture *t : textures_)
        SDL_DestroyTexture(t);

    textures_.clear();
    surfaces_.clear();
}

SDL_Texture *TexturePack::GetTexture(Texture id) const
{
    if (textures_[static_cast<int>(id)] == nullptr)
        return textures_[static_cast<int>(Texture::Error)];
    return textures_[static_cast<int>(id)];
}