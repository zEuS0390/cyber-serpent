#include <random>
#include <ctime>
#include "windowGrid.h"
#include "food.h"
#include "constants.h"

using std::uniform_int_distribution;
using sf::Vector2f;
using sf::Color;
using constants::WINDOW_SIZEX;
using constants::WINDOW_SIZEY;

food::food (Vector2f rectSize, unsigned int scale)
:   RectangleShape(rectSize),
    isHit(false),
    scale(scale),
    eng(time(NULL)) {
    setFillColor(Color(0, 255, 0));
}

void food::setRandomPosition () {
    while (true) {
        uniform_int_distribution<int> distrX(scale, WINDOW_SIZEX - scale * 2);
        uniform_int_distribution<int> distrY(scale, WINDOW_SIZEY - scale * 2);
        unsigned int x = distrX(eng);
        unsigned int y = distrY(eng);
        if (x % scale == 0 && y % scale == 0) {
            setPosition(Vector2f(x, y));
            break;
        }
    }
    return;
}
