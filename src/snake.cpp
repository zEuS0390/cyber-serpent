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
	snakePos.emplace_front(x, y);
	snakePos.emplace_front(x*2, y);
	snakePos.emplace_front(x*3, y);
	snakeBody.emplace(x, y);
	snakeBody.emplace(x*2, y);
	snakeBody.emplace(x*3, y);
}
