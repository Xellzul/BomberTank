/**
 * @file e_direction.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of Direction enum
 * @date 2020-06-06
 */
#ifndef E_DIRECTION_H
#define E_DIRECTION_H

/**
 * @enum Direction
 * @brief Contains all possible Directions including `no direction`
 */
enum class Direction
{
    None,
    Up,
    Down,
    Left,
    Right
};

#endif