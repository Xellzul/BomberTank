/**
 * @file e_textures.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Texture enum
 * @date 2020-06-06
 */
#ifndef E_TEXTURES_H
#define E_TEXTURES_H

/**
 * @enum Texture
 * @brief All textures used by Tank game
 */
enum class Texture : int
{
    Error = 0,
    Air = 1,
    TankUp = 2,
    TankLeft = 3,
    TankDown = 4,
    TankRight = 5,
    Bricks = 6,
    Explosion1 = 7,
    Explosion2 = 8,
    Explosion3 = 9,
    Explosion4 = 10,
    Steel = 11,
    Ammo = 12,
    Crate = 13,
    Projectile = 14,
    Health = 15,
    Speed = 16,
    Repair = 17
};

#endif