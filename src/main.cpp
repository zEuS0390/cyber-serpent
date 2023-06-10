#include "snakeGame.h"

/*
 ---------------------------------------------------------
 * CREATED BY: zEuS-0390
 * DATE CREATED: APRIL 18, 2020; SATURDAY
 * DESCRIPTION: This is the main code for the snake game.
 ---------------------------------------------------------
*/

// Structure for x and y axes
struct axes {
    float x;
    float y;
};

// Main execution of the program
int main () {
    struct axes windowSize = {640, 480};
    snakeGame sg(windowSize.x, windowSize.y, "Snake Game");
    return 0;
}
