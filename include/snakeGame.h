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
                     const char*);
    private:
        int  score;
        bool isRunning;
        bool isHit;
    private:
        void updates                (void);
        void events                 (void);
        void render                 (float);
        void mainLoop               (void);
        void renderGrid             (void);
        void renderSnake            (void);
        void resetGame              (void);
    private:
        std::vector<sf::RectangleShape> snakeRects;
    private:
        Colors                  colors;
        SoundManager		soundManager;
        snake                   snakeObj;
        windowGrid              winGrid;
        food                    foodObj;
        sf::RenderWindow        window;
        intro                   introduction;
        sf::Clock               clock;
        sf::Clock               menuClock;
        sf::Clock               scoreClock;
        Anim                    anim;
        sf::Vector2f            lastFoodPos;
        Interface               interface;
};

#endif
