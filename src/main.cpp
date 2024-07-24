#include "snakeGame.hpp"
#include "constants.hpp"

/*
 ---------------------------------------------------------
 * CREATED BY: zEuS0390
 * DATE CREATED: APRIL 18, 2020; SATURDAY
 * DESCRIPTION: This is the main code for the snake game.
 ---------------------------------------------------------
*/

using constants::WINDOW_TITLE;
using constants::WINDOW_SIZEX;
using constants::WINDOW_SIZEY;

// Main execution of the program
int main () {
	snakeGame cs(WINDOW_SIZEX, WINDOW_SIZEY, WINDOW_TITLE);
	return 0;
}
