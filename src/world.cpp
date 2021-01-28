/**
 * @file world.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of World class
 * @date 2020-06-09
 */
#include "world.hpp"

#include "GameObjects/tile_air.hpp"
#include "GameObjects/tile_steel.hpp"
#include "GameObjects/tile_bricks.hpp"
#include "GameObjects/tile_crate.hpp"

#include "GameObjects/ai_tank.hpp"
#include "GameObjects/tank.hpp"

#include <algorithm>

#include <fstream>
#include <iostream>

#include <cmath>
#include <iostream>

#include "tank_game.hpp"

World::World() = default;

World::~World()
{
    ClearWorld();
}

Tile *World::SetBlock(int x, int y, Tile *newTile)
{
    newTile->SetLocation(Point2D(x, y));
    int index = y * GetWidth() + x;
    Tile *block = worldData_.at(index);

    worldData_.at(index) = newTile;

    delete block;

    return newTile;
}

Tile *World::GetBlock(int x, int y) const
{
    int index = y * GetWidth() + x;
    if (x >= (int)GetWidth() || y >= (int)GetHeigth() || x < 0 || y < 0)
        return nullptr;
    return worldData_.at(index);
}

size_t World::GetWidth() const
{
    return width_;
}

size_t World::GetHeigth() const
{
    return heigth_;
}

const std::vector<Tile *> &World::GetBlocks() const
{
    return worldData_;
}
const std::vector<Entity *> &World::GetEntities() const
{
    return entities_;
}
const std::vector<Tank *> &World::GetPlayers() const
{
    return players_;
}

const std::vector<IPhysical *> World::GetCollisions(Point2D pos, Point2D size) const
{
    std::vector<IPhysical *> toReturn;

    //get tile collisions
    for (int x = std::max((int)pos.x, 0); x < ceil(pos.x + size.x); x++)
    {
        for (int y = std::max((int)pos.y, 0); y < ceil(pos.y + size.y); y++)
        {
            auto block = GetBlock(x, y);
            if (block == nullptr)
                continue;
            toReturn.emplace_back(block);
        }
    }

    //get entity collisions
    for (Entity *e : entities_)
    {
        if (e->Intersects(pos, size))
            toReturn.emplace_back(e);
    }

    return toReturn;
}

void World::ChangeTile(Tile *t)
{
    toChange_.emplace_back(t);
}

void World::SpawnEntity(Entity *e)
{
    toSpawn_.emplace_back(e);
}

void World::DeleteEntity(Entity *e)
{
    toDelete_.emplace(e);
}

void World::Update(const GameContext &context)
{
    //do the tick
    for (auto e : GetEntities())
        e->Update(context);

    for (auto b : GetBlocks())
        b->Update(context);

    //check for collision
    for (auto a : GetEntities())
    {
        auto col = GetCollisions(a->GetLocation(), a->GetSize());
        for (auto b : col)
        {
            b->Collide(context, *a);
            a->Collide(context, *b);
        }
    }

    //Clean deleted entities
    for (Entity *e : toDelete_)
    {
        auto iter = std::find(entities_.begin(), entities_.end(), e);
        if (iter != entities_.end())
            entities_.erase(iter);

        if (dynamic_cast<Tank *>(e))
        {
            tanks_--;
            if (tanks_ <= 1)
                context.GetTankGame()->run_ = false;

            //if it is player
            auto iterPlayers = std::find(players_.begin(), players_.end(), e);
            if (iterPlayers != players_.end())
            {
                players_.erase(iterPlayers);
                context.GetTankGame()->OnPlayerDeath();
            }
        }

        delete e;
    }

    toDelete_.clear();

    for (Tile *t : toChange_)
    {
        Point2D loc = t->GetLocation();
        SetBlock(loc.x, loc.y, t);
    }
    toChange_.clear();

    for (Entity *e : toSpawn_)
        entities_.emplace_back(e);
    toSpawn_.clear();
}

void World::ClearWorld()
{
    for (Tile *a : worldData_)
        delete a;

    for (Entity *e : entities_)
        delete e;

    for (Entity *e : toSpawn_)
        delete e;

    for (Tile *e : toChange_)
        delete e;

    worldData_.clear();
    entities_.clear();
    players_.clear();

    toSpawn_.clear();
    toDelete_.clear();
    toChange_.clear();
}

bool World::LoadWorld(std::string &filename, size_t players)
{
    ClearWorld();

    std::ifstream ifs(filename.c_str());

    if (ifs.fail())
    {
        std::cerr << "Cannot open world: \"" << filename << "\"" << std::endl;
        return false;
    }

    tanks_ = 0;

    int id;

    //header
    ifs >> width_;
    ifs >> heigth_;
    if (heigth_ <= 0 || width_ <= 0)
    {
        std::cerr << "Invalid world header format" << std::endl;
        return false;
    }

    worldData_ = std::vector<Tile *>(heigth_ * width_, nullptr);

    for (size_t y = 0; y < heigth_; y++)
    {
        for (size_t x = 0; x < width_; x++)
        {
            ifs >> id;

            //check for valid format
            if (ifs.fail())
            {
                std::cerr << "Error reading map at <" << x << "," << y << ">" << std::endl;
                return false;
            }

            if (!HandleBlock(x, y, id, players))
            {
                std::cerr << "Cannot process block id: " << id << std::endl;
                return false;
            }
        }
    }

    return true;
}

bool World::HandleBlock(int x, int y, int id, int targetPlayerTanks)
{
    switch (id)
    {
    case 0:
        SetBlock(x, y, new TileAir());
        return true;
    case 1:
        SetBlock(x, y, new TileSteel());
        return true;
    case 2:
    {
        SetBlock(x, y, new TileAir());

        tanks_++;

        Tank *tank;
        if (targetPlayerTanks > (int)players_.size())
        {
            tank = new Tank();
            players_.emplace_back(tank);
        }
        else
            tank = new AITank();

        tank->SetLocation(Point2D(x, y));
        entities_.emplace_back(tank);
        return true;
    }
    case 3:
        SetBlock(x, y, new TileBricks());
        return true;
    case 4:
    {
        SetBlock(x, y, new TileAir());

        tanks_++;

        AITank *tank = new AITank();
        tank->SetLocation(Point2D(x, y));
        entities_.emplace_back(tank);
        return true;
    }
    case 5:
        SetBlock(x, y, new TileCrate());
        return true;
    default:
        return false;
    }
    return false;
}

int World::ActiveTanks() const
{
    return tanks_;
}