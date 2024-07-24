#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include "windowGrid.hpp"
#include "snake.hpp"

using std::mt19937;
using sf::RectangleShape;
using sf::Vector2f;

class food: public RectangleShape 
{
public:
	bool isHit;
	food                    (Vector2f, unsigned int);
	void setRandomPosition  (const snake&);
private:
        mt19937 eng;
	unsigned int scale;
};

#endif
