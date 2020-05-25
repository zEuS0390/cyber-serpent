#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include <vector>

struct direction {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

// snake class
class snake {
    public:
        bool isMoving;
    public:
        snake                   (void);
        void movement           (int);
        void increment          (void);
        void initHeadPos        (unsigned int, unsigned int);
    public:
        struct direction dir;
        std::vector<sf::Vector2f> snakePos;
};

#endif
