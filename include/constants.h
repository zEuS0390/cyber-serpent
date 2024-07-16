#ifndef CONSTANTS_H 
#define CONSTANTS_H

#include <string>

namespace constants {
	constexpr const char*	WINDOW_TITLE =		"Snake Game";
	constexpr unsigned int	WINDOW_SIZEX =		640;
	constexpr unsigned int	WINDOW_SIZEY =		480;
	constexpr unsigned int	GRID_SCALE =		20;
	const std::string	FONT_FILENAME =		"november.ttf";
	const std::string	SOUND_DEAD =		"sfx/dead.wav";
	const std::string	SOUND_FOOD =		"sfx/food.wav";
	const std::string	SOUND_PORTAL =		"sfx/portal.wav";
	const std::string	SOUND_SNAKE =		"sfx/snake.wav";
	const std::string	SOUND_BUTTON_UP =	"sfx/button_up.wav";
	const std::string	SOUND_BUTTON_DOWN =	"sfx/button_down.wav";
	const std::string	SOUND_BUTTON_ENTER =	"sfx/button_enter.wav";
	const std::string	SOUND_QUIT =		"sfx/quit.wav";
	const std::string	SOUND_BLIP =		"sfx/blip.wav";
}

#endif
