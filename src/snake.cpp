#include <SFML/Graphics.hpp>
#include "snake.h"
#include <iostream>

// snake class constructor
snake::snake(void)
:   isMoving(false),
    dir{false, false, false, true} {
}

void snake::movement (int speed) {
    if (dir.up) {
        sf::Vector2f temp = sf::Vector2f(snakePos.back().x, snakePos.back().y - speed);
        snakePos.insert(snakePos.end(), temp);
    } else if (dir.down) {
        sf::Vector2f temp = sf::Vector2f(snakePos.back().x, snakePos.back().y + speed);
        snakePos.insert(snakePos.end(), temp);
    } else if (dir.left) {
        sf::Vector2f temp = sf::Vector2f(snakePos.back().x - speed, snakePos.back().y);
        snakePos.insert(snakePos.end(), temp);
    } else if (dir.right) {
        sf::Vector2f temp = sf::Vector2f(snakePos.back().x + speed, snakePos.back().y);
        snakePos.insert(snakePos.end(), temp);
    }
    snakePos.erase(snakePos.begin());
    return;
}

void snake::increment (void) {
    sf::Vector2f temp = sf::Vector2f(snakePos.front().x, snakePos.front().y);
    snakePos.insert(snakePos.begin(), temp);
    return;
}

void snake::initHeadPos (unsigned int x, unsigned int y) {
    snakePos.push_back(sf::Vector2f(x, y));
    snakePos.push_back(sf::Vector2f(x+x, y));
    snakePos.push_back(sf::Vector2f(x+x+x, y));
    return;
}
