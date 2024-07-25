#include <SFML/Graphics.hpp>
#include <iostream>
#include "snake.hpp"

using sf::Vector2f;

// snake class constructor
snake::snake()
:   isMoving(false),
    dir{false, false, false, true} 
{
}

void snake::increment () 
{
	Vector2f newPos = snakePos.back();
	snakePos.push_back(newPos);
	snakeBody.insert(newPos);
}

void snake::initHeadPos (const unsigned int& x, const unsigned int& y) 
{
	for (int i = 1; i <= 3; ++i) {
		snakePos.emplace_front(x*i, y);
		snakeBody.emplace(x*i, y);
	}
}
