#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <deque>
#include "utils.hpp"

using sf::Vector2f;
using std::unordered_set;
using std::deque;

struct direction
{
    bool up {false};
    bool down {false};
    bool left {false};
    bool right {false};
};

// snake class
class snake
{
public:
        bool					isMoving;
	struct					direction dir;
	unordered_set<Vector2f, Vector2fHash>	snakeBody;
	deque<Vector2f> 			snakePos;
        snake                   		();
        void movement           		(int);
        void increment          		();
        void initHeadPos        		(const unsigned int&, const unsigned int&);
};

#endif
