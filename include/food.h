#ifndef FOOD_H
#define FOOD_H
#include <SFML/Graphics.hpp>
#include <random>
#include "windowGrid.h"

class food: public sf::RectangleShape {
    public:
        bool isHit;
    private:
        unsigned int scale;
    public:
        food                    (sf::Vector2f, unsigned int);
        void setRandomPosition  (void);
    private:
        std::mt19937 eng;
};

#endif
