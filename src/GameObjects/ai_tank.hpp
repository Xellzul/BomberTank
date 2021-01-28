/**
 * @file ai_tank.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of AI TAnk class
 * @date 2020-06-07
 */
#ifndef AI_TANK_H
#define AI_TANK_H

#include "tank.hpp"

/**
 * @brief AI version of Tank, doesnt need to be moved by player
 */
class AITank : public Tank
{
public:
    /**
     * @brief Construct a new AITank object
     */
    AITank();
    /**
     * @brief Destroy the AITank object
     */
    virtual ~AITank();

    void Update(const GameContext &context);

private:
    /**
     * @brief Updates AI of tank
     * @param context Game Context
     */
    void UpdateAI(const GameContext &context);

    /**
     * @brief Calculates value - weight of firing given direction
     * @param context Game Context
     * @param dir Direction to fire
     * @return int weight
     */
    int CalculateFireWeight(const GameContext &context, Direction dir) const;
    /**
     * @brief Calculates value - weight of going given direction
     * @param context Game Context
     * @param dir Direction to fire
     * @return int weight
     */
    int CalculateMovementWeight(const GameContext &context, Direction dir) const;
    /**
     * @brief Tells if it is meaningful to go to given direction
     * @param context Game Context
     * @param dir Direction to check
     * @return true if its meaningful
     * @return false if it is not meaningful
     */
    bool CanGoDirection(const GameContext &context, Direction dir) const;

    //tick when AI needs update
    size_t nextAIUpdate_ = 0;
};

#endif