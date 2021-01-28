/**
 * @file texture_pack.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Texture Pack class
 * @date 2020-06-07
 */
#ifndef TEXTURE_PACK_H
#define TEXTURE_PACK_H

#include <string>
#include <vector>

#include <SDL2/SDL_image.h>

#include "e_textures.hpp"

/**
 * @brief Manages game texture for SDL
 * loads them and safe presents them
 */
class TexturePack
{
public:
    /**
     * @brief Construct a new Texture Pack object
     * @param renderer SDL renderer
     * @param folder to load Textures from
     * @param debugMode gives more output to terminal
     */
    TexturePack(SDL_Renderer *renderer, const std::string &folder, bool debugMode);
    /**
     * @brief Destroy the Texture Pack object
     */
    ~TexturePack();

    /**
     * @brief Get SDL Texture
     * if the texture was not loaded then returns error texture
     * @param texture to get
     * @return SDL_Texture* texture
     */
    SDL_Texture *GetTexture(Texture texture) const;

private:
    std::vector<SDL_Texture *> textures_;
    std::vector<SDL_Surface *> surfaces_;
    SDL_Renderer *renderer_;

    //error image in case everything goes wrong
    constexpr static unsigned short errorImage[] = {
        0x5089, 0x474e, 0x0a0d, 0x0a1a, 0x0000, 0x0d00, 0x4849, 0x5244,
        0x0000, 0x2000, 0x0000, 0x2000, 0x0608, 0x0000, 0x7300, 0x7a7a,
        0x00f4, 0x0000, 0x7304, 0x4942, 0x0854, 0x0808, 0x7c08, 0x6408,
        0x0088, 0x0000, 0x4930, 0x4144, 0x5854, 0xed85, 0x31ce, 0x0001,
        0x0c20, 0xb0c0, 0x7f82, 0x1835, 0x321c, 0xa4f6, 0x9a06, 0x9af3,
        0xb169, 0x39bb, 0x0007, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0xa800, 0x65fa, 0x0218, 0x0df0, 0x9829, 0x0053, 0x0000,
        0x4900, 0x4e45, 0xae44, 0x6042, 0x0082};
};

#endif