#include <random>
#include <ctime>
#include "windowGrid.h"
#include "food.h"

food::food (sf::Vector2f rectSize, unsigned int scale)
:   RectangleShape(rectSize),
    isHit(false),
    scale(scale),
    eng(time(NULL)) {
    setFillColor(sf::Color(0, 255, 0));
}

void food::setRandomPosition (void) {
    while (true) {
        std::uniform_int_distribution<int> distrX(scale, 640-scale*2);
        std::uniform_int_distribution<int> distrY(scale, 480-scale*2);
        unsigned int x = distrX(eng);
        unsigned int y = distrY(eng);
        if (x%scale == 0 && y%scale == 0) {
            setPosition(sf::Vector2f(x, y));
            break;
        }
    }
    return;
}
