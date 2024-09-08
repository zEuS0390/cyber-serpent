#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <queue>
#include "windowGrid.hpp"
#include "interface.hpp"
#include "snake.hpp"
#include "sound.hpp"
#include "intro.hpp"
#include "food.hpp"
#include "anim.hpp"

using std::string;
using std::vector;
using sf::RectangleShape;
using sf::Font;
using sf::RenderWindow;
using sf::Clock;
using sf::Vector2f;

struct Colors
{
    bool up;
    bool right;
    bool down;
    bool left;
};

// snakeGame class
class SnakeGame
{
public:
    SnakeGame               (const unsigned int, const unsigned int, const string&);
    void run                ();
private:
    int  score;
    bool isRunning;
    bool isHit;
    void updates            ();
    void events             ();
    void render             (const float&);
    void renderGrid         ();
    void renderSnake        ();
    void resetGame          ();
    vector<RectangleShape>  snakeRects;
    Font                    font;
    Colors                  colors;
    SoundManager            soundManager;
    snake                   snakeObj;
    windowGrid              winGrid;
    food                    foodObj;
    RenderWindow            window;
    intro                   introduction;
    Clock                   clock;
    Clock                   menuClock;
    Clock                   scoreClock;
    Anim                    anim;
    Vector2f                lastFoodPos;
    Interface               interface;
};

#endif

