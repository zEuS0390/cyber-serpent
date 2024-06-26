#include <SFML/Graphics.hpp>
#include "snake.h"
#include <iostream>

// snake class constructor
snake::snake()
:   isMoving(false),
    dir{false, false, false, true} {
}

void snake::increment () {
    sf::Vector2f pos = snakePos.front();
    snakePos.insert(snakePos.begin(), pos);
    return;
}

void snake::initHeadPos (unsigned int x, unsigned int y) {
    snakePos.push_back(sf::Vector2f(x, y));
    snakePos.push_back(sf::Vector2f(x+x, y));
    snakePos.push_back(sf::Vector2f(x+x+x, y));
    return;
}
