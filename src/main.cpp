/**
 * @file main.cpp
 * @author Hlvaty Adrian (hlavaadr@fit.cvut.cz)
 * @brief main file for this application
 * contains entrypoint for this source code and all argument handling
 * @date 2020-06-06
 * 
 * @mainpage Tanks
 * @section MapFile-structure
 * WIDTH <WHITESPACE> HEIGHT <WHITESPACE> (WIDTH*HEIGHT times)(ID <WHITESPACE>) \n
 *  where WIDTH and HEIGHT is size of map and ID is proccessed in HandleBlock method
 *  of World class
 * 
 *  @subsection Example of map 4 width 5 tall
 *  ///START OF FILE \n
 *  4 5 \n
 *  1 1 1 1 \n
 *  1 2 0 1 \n
 *  1 0 0 1 \n
 *  1 0 3 1 \n
 *  1 1 1 1 \n
 *  ///END OF FILE \n
 */

#include <iostream>
#include <string>
#include <argp.h>

#include "tank_game.hpp"
#include "sdl_io_device.hpp"
#include "dummy_io_device.hpp"

/**
 * @brief how does the input help message look like
 */
static char args_doc[] = "<ASSET FOLDER> <MAP FILE>";

/**
 * @brief All possible Argmunets
 */
struct Arguments
{
    std::string mapFile = "";
    std::string assetFolder = "";
    int resolution = 32;
    /**
     * @brief Controlls what IO device will be passed to game
     * False = Dummy io device
     * TRue = SDL device
     */
    bool graphics = true;
    bool secondPlayer = false;
    bool debugMode = false;
};

/**
 * @brief ARGP Callback for parsing arguments
 * @param key key of argument
 * @param arg possible text associated with argument
 * @param state 
 * @return error_t error
 */
static error_t parseArgument(int key, char *arg, struct argp_state *state)
{
    Arguments *arguments = (Arguments *)(state->input);
    switch (key)
    {
    case 'g':
        arguments->graphics = false;
        break;
    case 'm':
        arguments->secondPlayer = true;
        break;
    case 'd':
        arguments->debugMode = true;
        break;
    case 'r':
        int resolution;
        try
        {
            resolution = std::stoi(arg);
            if (resolution < 1 || resolution > 255)
                throw std::out_of_range("stoi");
            arguments->resolution = resolution;
        }
        catch (std::exception &e)
        {
            argp_failure(state, 1, 0, "Invalid resolution, must be in range of 1 to 255");
            return 1;
        }
        break;

    case ARGP_KEY_ARG:
        if (state->arg_num == 0)
            arguments->assetFolder.assign(arg);
        else if (state->arg_num == 1)
            arguments->mapFile.assign(arg);
        break;
    case ARGP_KEY_END:
        if (state->arg_num > 2)
        {
            argp_failure(state, 1, 0, "too many arguments");
            argp_usage(state);
            return 1;
        }
        else if (state->arg_num < 2)
        {
            argp_usage(state);
            return 1;
        }
        break;

    default:
        break;
    }
    return 0;
}

/**
 * @brief Entry point
 * @param argc argument count
 * @param argv arguments
 * @return int app return value 
 */
int main(int argc, char **argv)
{
    //Arguments handling
    argp_option options[] = {
        {"graphics", 'g', 0, 0, "disables graphics output"},
        {"debug", 'd', 0, 0, "enables debug mode"},
        {"multiplayer", 'm', 0, 0, "play with second player"},
        {"resolution", 'r', "NUM", 0, "Resolution [default=32] in range <1, 255>"},
        {0}};

    argp argp = {options, parseArgument, args_doc, 0};

    Arguments arguments;

    auto result = argp_parse(&argp, argc, argv, ARGP_NO_EXIT, 0, &arguments);

    if (result != 0)
        exit(result);

    //running game
    IODevice *device;
    if (arguments.graphics)
    {
        SDLIODevice *dev;
        try
        {
            dev = new SDLIODevice(arguments.resolution);
            dev->LoadTextures(arguments.assetFolder, arguments.debugMode);
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return 1;
        }

        device = dev;
    }
    else
        device = new DummyIODevice();

    TankGame tg(device, arguments.debugMode);
    tg.StartGame(arguments.mapFile, arguments.secondPlayer);

    delete device;
}