/**
 * @file world.hpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Definition of World class
 * @date 2020-06-09
 */
#ifndef WORLD_H
#define WORLD_H

#include <set>
#include <vector>
#include <string>

#include "tile.hpp"
#include "entity.hpp"
#include "GameObjects/tank.hpp"

/**
 * @brief World manages all map tiles and all entities on the map tiles
 */
class World
{
public:
    /**
     * @brief Construct a new World object
     */
    World();
    /**
     * @brief Destroy the World object
     */
    ~World();

    /**
     * @brief Updates everything
     * Updates all tiles and Entities on map
     * Deletes all entites marked for deletion
     * Spawns all entities marked for spawn
     * @param context Game Context
     */
    void Update(const GameContext &context);

    /**
     * @brief Changes block at coordinations
     * this replaces block at given coordinations with new one
     * and deletes old. 
     * This is not safe to use inside Tick!
     * @param x possition on x axis
     * @param y possition on y axis
     * @param newTile tile to place
     * @return Tile* tile that was spawned
     */
    Tile *SetBlock(int x, int y, Tile *newTile);
    /**
     * @brief Get block at specific coordinations
     * @param x possition on x axis
     * @param y possition on y axis
     * @return Tile* tile that was found
     */
    Tile *GetBlock(int x, int y) const;
    /**
     * @brief Get Width of the world
     * @return size_t 
     */
    size_t GetWidth() const;
    /**
     * @brief Get Heigth of the world
     * @return size_t 
     */
    size_t GetHeigth() const;

    /**
     * @brief Get all Players
     * @return const std::vector<Tank *>&  All players
     */
    const std::vector<Tank *> &GetPlayers() const;
    /**
     * @brief Get all Tiles / Blocks
     * @return const std::vector<Tile *>& All blocks / tiles
     */
    const std::vector<Tile *> &GetBlocks() const;
    /**
     * @brief Get all Entities
     * @return const std::vector<Entity *>& All entities
     */
    const std::vector<Entity *> &GetEntities() const;

    /**
     * @brief Performs Collision check agaist rectangle
     * @param pos position of rectangle (top left)
     * @param size size of rectangle
     * @return const std::vector<IPhysical *> All colliding objects
     */
    const std::vector<IPhysical *> GetCollisions(Point2D pos, Point2D size) const;

    /**
     * @brief Replaces tile with new tile at end of tick
     * this is safe to use inside Update method
     * @param t tile to replace
     */
    void ChangeTile(Tile *t);
    /**
     * @brief Spawn Entity at end of tick
     * @param e entity to spawn
     */
    void SpawnEntity(Entity *e);
    /**
     * @brief Deletes Entity at end of tick
     * this method resolves duplicite deletion
     * @param e entity to delete
     */
    void DeleteEntity(Entity *e);

    /**
     * @brief Loads world from mapFile, is safe to be called multiple times
     * @param filename filename to load world from
     * @param players number of players playing
     * @return true if load was successful
     * @return false if load was unsuccessful
     */
    bool LoadWorld(std::string &filename, size_t players);

    /**
     * @brief Tells how many tanks are active
     * @return int number of tanks
     */
    int ActiveTanks() const;

private:
    /**
     * @brief Converts map id to actual tile and/or Entity and puts it in the world 
     * @param x where to put it on x axis
     * @param y where to put it on y axis
     * @param id map id to put in the world
     * @param targetPlayerTanks how many tanks players want to play
     * @return true if everything is ok
     * @return false if something went wrong (eg invalid id) 
     */
    bool HandleBlock(int x, int y, int id, int targetPlayerTanks);

    /**
     * @brief frees all allocated / managed data by World
     */
    void ClearWorld();

    //number of active tanks
    int tanks_ = 0;

    //world dimensions
    size_t width_, heigth_;

    //all world tiles
    std::vector<Tile *> worldData_;
    //all world entities
    std::vector<Entity *> entities_;

    //active human players
    std::vector<Tank *> players_;

    //entities to spawn
    std::vector<Entity *> toSpawn_;
    //entities to delete
    std::set<Entity *> toDelete_;
    //tiles to replace
    std::vector<Tile *> toChange_;
};

#endif