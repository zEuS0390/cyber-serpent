#include <random>
#include <ctime>
#include "windowGrid.hpp"
#include "constants.hpp"
#include "snake.hpp"
#include "food.hpp"

using std::uniform_int_distribution;
using sf::Vector2f;
using sf::Color;
using constants::WINDOW_SIZEX;
using constants::WINDOW_SIZEY;

food::food (Vector2f rectSize, unsigned int scale)
:       RectangleShape(rectSize),
        isHit(false),
        scale(scale),
        eng(time(nullptr))
{
        setFillColor(Color(0, 255, 0));
}

void food::setRandomPosition (const snake& snakeObj)
{
        uniform_int_distribution<unsigned int> distrX(scale, WINDOW_SIZEX - scale * 2);
        uniform_int_distribution<unsigned int> distrY(scale, WINDOW_SIZEY - scale * 2);

        const auto& head = snakeObj.snakePos.front();
        const auto& snakeBody = snakeObj.snakeBody;

        while (true)
        {
                unsigned int x, y;
                x = distrX(eng);
                y = distrY(eng);
                if (x % scale == 0 && y % scale == 0 &&
                    snakeBody.find(Vector2f(x, y)) == snakeBody.end() &&
                    x != head.x && y != head.y)
                {
                        this->setPosition(Vector2f(x, y));
                        break;
                }
        }
}

