/**
 * @file tank_game.cpp
 * @author Hlavaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief Implementation of Tank Game class
 * @date 2020-06-09
 */

#include "tank_game.hpp"

#include "game_context.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

TankGame::TankGame(IODevice *ioDevice, bool debug) : debug_(debug), iodevice_(ioDevice)
{
    context_.SetTankGame(this);
}

TankGame::~TankGame()
{
    delete world_;
    world_ = nullptr;
}

void TankGame::StartGame(std::string &mapName, bool secondPlayer)
{
    std::random_device dev;

    mapName_ = mapName;

    world_ = new World();

    if (!world_->LoadWorld(mapName, secondPlayer ? 2 : 1))
        return;

    iodevice_->OnWorldSizeChange(*world_);

    context_.SetRandom(new std::mt19937(dev()));
    context_.SetWorld(world_);

    Run();
}

World &TankGame::GetWorld() const
{
    return *world_;
}

void TankGame::HandleInput(InputEvent e)
{
    Tank *p1 = nullptr;
    Tank *p2 = nullptr;

    if (world_->GetPlayers().size() >= 1)
        p1 = world_->GetPlayers().at(0);
    if (world_->GetPlayers().size() >= 2)
        p2 = world_->GetPlayers().at(1);

    switch (e)
    {
    case InputEvent::Quit:
        run_ = false;
        force_end_ = true;
        break;
    case InputEvent::Player1Left:
        if (p1)
            p1->SetDirection(Direction::Left);
        break;

    case InputEvent::Player1Up:
        if (p1)
            p1->SetDirection(Direction::Up);
        break;

    case InputEvent::Player1Right:
        if (p1)
            p1->SetDirection(Direction::Right);
        break;

    case InputEvent::Player1Down:
        if (p1)
            p1->SetDirection(Direction::Down);
        break;
    case InputEvent::Player1Fire:
        if (p1)
            p1->Fire(context_);
        break;

    case InputEvent::Player2Left:
        if (p2)
            p2->SetDirection(Direction::Left);
        break;

    case InputEvent::Player2Up:
        if (p2)
            p2->SetDirection(Direction::Up);
        break;

    case InputEvent::Player2Right:
        if (p2)
            p2->SetDirection(Direction::Right);
        break;

    case InputEvent::Player2Down:
        if (p2)
            p2->SetDirection(Direction::Down);
        break;
    case InputEvent::Player2Fire:
        if (p2)
            p2->Fire(context_);
        break;
    }
}

void TankGame::Run()
{
    std::cout << "Tank Game Starting..." << std::endl;
    run_ = true;

    auto tick0time = std::chrono::steady_clock::now();
    auto lastTickEnd = std::chrono::steady_clock::now();

    while (run_ && !force_end_)
    {
        std::vector<InputEvent> inputs = iodevice_->GetInputEvents();

        for (InputEvent i : inputs)
            HandleInput(i);

        world_->Update(context_);

        iodevice_->Render(*world_, context_);

        tick_++;

        if (tick_ % 61 == 0 && debug_)
        {
            std::chrono::duration<double, std::milli> tickTime = std::chrono::steady_clock::now() - lastTickEnd;
            std::cout << "Tick <" << tick_ << "> took: " << tickTime.count() << "ms" << std::endl;
            std::chrono::duration<double> totalElapsed = std::chrono::steady_clock::now() - tick0time;
            std::cout << "FPS: " << tick_ / totalElapsed.count() << std::endl;
        }

        std::this_thread::sleep_until(lastTickEnd + std::chrono::microseconds(1000000 / 60));
        lastTickEnd = std::chrono::steady_clock::now();
    }

    //calculate score
    if (isSinglePlayer() && !force_end_)
    {
        std::chrono::duration<double, std::milli> totalElapsed = std::chrono::steady_clock::now() - tick0time;
        score_ = INT32_MAX / totalElapsed.count();

        if (world_->GetPlayers().size() == 0) // still alive => won
        {
            score_ = 0;
        }

        std::filesystem::path mapPath(mapName_);
        std::string realMapName = mapPath.filename();

        int prevScore = ReadScore(realMapName);
        bool scoreWrite = true;

        if (prevScore == -1)
            std::cout << "This is first play on this map!" << std::endl;
        else if (prevScore >= score_)
            std::cout << "HighScore on this map is: " << prevScore << std::endl;
        else
            std::cout << "Previous high score was:" << prevScore << std::endl;

        if (score_ > prevScore && score_ >= 0)
        {
            if (score_ != 0)
                std::cout << "Congratualtion for new High Score!" << std::endl;
            scoreWrite = WriteScore(realMapName, score_);
        }

        std::cout << "Your score was: " << score_ << std::endl;

        if (!scoreWrite)
            std::cout << "Ups, someting went wrong, could write new High Score" << std::endl;
    }
}

size_t TankGame::GetTick() const
{
    return tick_;
}

const TankGame &TankGame::printDebug(const std::string &text) const
{
    if (debug_)
        std::cout << text << std::flush;
    return *this;
}

bool TankGame::isSinglePlayer() const
{
    return !vsPlayer_;
}

int TankGame::GetScore() const
{
    return score_;
}

void TankGame::OnPlayerDeath()
{
    //1 player left
    if (world_->ActiveTanks() == 1 && world_->GetPlayers().size() == 1)
        run_ = false;

    //no player left
    if (world_->GetPlayers().size() < 1)
        run_ = false;
}

int TankGame::ReadScore(std::string &map)
{
    int score;

    printDebug("Reading score from: scores/").printDebug(map).printDebug("\n");

    std::ifstream ifs("scores/" + map);
    if (ifs.is_open())
        ifs >> score;

    if (ifs.fail() || ifs.bad())
        return -1;

    return score;
}

bool TankGame::WriteScore(std::string &map, int score)
{
    std::error_code err;
    std::filesystem::create_directory("scores", err);

    if (err)
        return false;

    std::ofstream ofs;
    ofs.open("scores/" + map, std::ios_base::app);
    ofs << score;
    ofs.flush();

    if (ofs.fail() || ofs.bad())
        return false;

    return true;
}