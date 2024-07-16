#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <queue>
#include "windowGrid.h"
#include "interface.h"
#include "snake.h"
#include "sound.h"
#include "intro.h"
#include "food.h"
#include "anim.h"

using std::string;
using std::vector;
using sf::RectangleShape;
using sf::Font;
using sf::RenderWindow;
using sf::Clock;
using sf::Vector2f;

struct Colors {
    bool up;
    bool right;
    bool down;
    bool left;
};

// snakeGame class
class snakeGame {
    public:
        snakeGame   (const unsigned int,
                     const unsigned int,
                     const string&);
    private:
        int  score;
        bool isRunning;
        bool isHit;
    private:
        void updates                ();
        void events                 ();
        void render                 (float);
        void mainLoop               ();
        void renderGrid             ();
        void renderSnake            ();
        void resetGame              ();
    private:
        vector<RectangleShape> snakeRects;
    private:
	Font			font;
        Colors                  colors;
        SoundManager		soundManager;
        snake                   snakeObj;
        windowGrid              winGrid;
        food                    foodObj;
        RenderWindow		window;
        intro                   introduction;
        Clock			clock;
        Clock			menuClock;
        Clock			scoreClock;
        Anim                    anim;
        Vector2f		lastFoodPos;
        Interface               interface;
};

#endif
