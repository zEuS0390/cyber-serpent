#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include "version.hpp"

namespace constants
{
    const std::string       WINDOW_TITLE =              "CyberSerpent";
    const std::string       GAME_VERSION =              constants::PROJECT_VERSION;
    constexpr unsigned int	WINDOW_SIZEX =              640;
    constexpr unsigned int	WINDOW_SIZEY =              480;
    constexpr unsigned int	GRID_SCALE =                20;
    const std::string       FONT_FILENAME =             "november.ttf";
    const std::string       SOUND_DEAD =                "sfx/dead.wav";
    const std::string       SOUND_FOOD =                "sfx/food.wav";
    const std::string       SOUND_PORTAL =              "sfx/portal.wav";
    const std::string       SOUND_SNAKE =               "sfx/snake.wav";
    const std::string       SOUND_BUTTON_UP =           "sfx/button_up.wav";
    const std::string       SOUND_BUTTON_DOWN =         "sfx/button_down.wav";
    const std::string       SOUND_BUTTON_ENTER =        "sfx/button_enter.wav";
    const std::string       SOUND_QUIT =                "sfx/quit.wav";
    const std::string       SOUND_BLIP =                "sfx/blip.wav";
    const std::string       IMAGE_SFML_LOGO =           "gfx/SFML_Logo.png";
    const std::string       IMAGE_CREATOR_LOGO =        "gfx/Creator_Logo.png";
    const std::string       FAILED_TO_LOAD_FILE_ERR =   "Failed to load file";
}

#endif

