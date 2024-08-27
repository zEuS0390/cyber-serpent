#include <SFML/Graphics.hpp>
#include <string>
#include "windowGrid.hpp"
#include "snakeGame.hpp"
#include "interface.hpp"
#include "constants.hpp"
#include "snake.hpp"
#include "sound.hpp"
#include "anim.hpp"
#include "utils.hpp"

using std::next;
using std::string;
using sf::Vector2f;
using sf::VideoMode;
using sf::Event;
using sf::Keyboard;
using sf::Color;
using sf::Vertex;
using sf::Lines;
using sf::RectangleShape;
using sf::Font;
using sf::Text;
using constants::FONT_FILENAME;

// snakeGame class constructor
SnakeGame::SnakeGame (const unsigned int winX,
                      const unsigned int winY,
                      const string& windowTitle)
:       score           (0),
        isRunning       (true),
        isHit           (false),
        colors          {true, false, false, false},
        winGrid         (winX, winY),
        foodObj         (Vector2f(winGrid.scale, winGrid.scale), winGrid.scale),
        window          (VideoMode(winX, winY), windowTitle),
        introduction    (window),
        anim            (window, winGrid.scale),
        interface       (&window)
{
	font.loadFromFile(FONT_FILENAME);
        introduction.init();
        window.setMouseCursorVisible(false);
        snakeObj.initHeadPos(winGrid.scale, winGrid.scale);
}

// Main loop of the game
void SnakeGame::run ()
{
	window.setFramerateLimit(10);
	while (isRunning)
	{
		float time {clock.getElapsedTime().asSeconds()};
		updates();
		events();
		render(time);
	}
}

// Handles events of the game
void SnakeGame::events ()
{
	Event event;
	bool is_keypressed {false};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case Event::Closed:
				window.close();
				break;
			case Event::LostFocus:
				if (!interface.isMenu)
					snakeObj.isMoving = false;
				break;
			case Event::GainedFocus:
				if (!interface.isMenu)
					snakeObj.isMoving = true;
				break;
			case Event::KeyPressed:
				if (!is_keypressed)
				{
					is_keypressed = true;
					if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up)
					{
						if (snakeObj.isMoving && !snakeObj.dir.up && !snakeObj.dir.down)
						{
							soundManager.playAudio("snake");
							snakeObj.dir = {true, false, false, false};
						}
						else if (interface.isMenu)
						{
							interface.menuSelect = (interface.menuSelect % 2) + 1;
							soundManager.playAudio("button_up");
						}
					}
					if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down)
					{
						if (snakeObj.isMoving && !snakeObj.dir.down && !snakeObj.dir.up)
						{
							soundManager.playAudio("snake");
							snakeObj.dir = {false, true, false, false};
						}
						else if (interface.isMenu)
						{
							interface.menuSelect = (interface.menuSelect % 2) + 1;
							soundManager.playAudio("button_down");
						}
					}
					if (event.key.code == Keyboard::A || event.key.code == Keyboard::Left)
					{
						if (snakeObj.isMoving && !snakeObj.dir.left && !snakeObj.dir.right)
						{
							soundManager.playAudio("snake");
							snakeObj.dir = {false, false, true, false};
						}
					}
					if (event.key.code == Keyboard::D || event.key.code == Keyboard::Right)
					{
						if (snakeObj.isMoving && !snakeObj.dir.right && !snakeObj.dir.left)
						{
							soundManager.playAudio("snake");
							snakeObj.dir = {false, false, false, true};
						}
					}
					if (event.key.code == Keyboard::Enter)
					{
						if (interface.isMenu)
						{
							if (interface.menuSelect == 1)
							{
								soundManager.playAudio("button_enter");
								interface.isMenu = false;
								snakeObj.isMoving = true;
								foodObj.setRandomPosition(snakeObj);
								score = 0;
							}
							else if (interface.menuSelect == 2)
							{
								isRunning = false;
							}
						}
					}
					if (event.key.code == Keyboard::Escape)
					{
						if (!interface.isMenu)
						{
							soundManager.playAudio("quit");
							anim.total = 0;
							score = 0;
							resetGame();
							interface.isMenu = true;
							snakeObj.isMoving = false;
						}
					}
				}
				break;
			case Event::KeyReleased:
				if (is_keypressed)
				{
					is_keypressed = false;
				}
				break;
		}
	}
}

// Handles updates of the game
void SnakeGame::updates()
{
    // If the snake is not moving, exit the function early
    if (!snakeObj.isMoving) return;

    // Retrieve and copy the current head position of the snake
    Vector2f head = snakeObj.snakePos.front();

    // Update the snake's body by inserting the current head position
    // and removing the last segment of the snake's body
    snakeObj.snakeBody.insert(head);
    snakeObj.snakeBody.erase(snakeObj.snakePos.back());

    // Calculate the new position of the current head copy based on the current direction
    if (snakeObj.dir.up)    head.y -= winGrid.scale;    // Move up
    if (snakeObj.dir.down)  head.y += winGrid.scale;    // Move down
    if (snakeObj.dir.left)  head.x -= winGrid.scale;    // Move left
    if (snakeObj.dir.right) head.x += winGrid.scale;    // Move right

    // Variable to track if the snake has crossed a portal boundary
    bool isPortalTriggered = false;

    // Check for boundary conditions to handle screen wrapping (portal logic)
    if (head.x < winGrid.scale)
    {
        // Snake has crossed the left boundary; wrap to the right side
        head.x = winGrid.winX - winGrid.scale * 2;
        colors = {false, false, false, true}; // Set colors for portal effect
        isPortalTriggered = true;
    }
    else if (head.x > winGrid.winX - winGrid.scale * 2)
    {
        // Snake has crossed the right boundary; wrap to the left side
        head.x = winGrid.scale;
        colors = {false, true, false, false};
        isPortalTriggered = true;
    }
    else if (head.y < winGrid.scale)
    {
        // Snake has crossed the top boundary; wrap to the bottom side
        head.y = winGrid.winY - winGrid.scale * 2;
        colors = {true, false, false, false};
        isPortalTriggered = true;
    }
    else if (head.y > winGrid.winY - winGrid.scale * 2)
    {
        // Snake has crossed the bottom boundary; wrap to the top side
        head.y = winGrid.scale;
        colors = {false, false, true, false};
        isPortalTriggered = true;
    }

    // Play the portal sound effect if the snake triggered a portal
    if (isPortalTriggered) soundManager.playAudio("portal");

    // Update the snake's position by adding the new head position to the front
    // and removing the last segment from the back
    snakeObj.snakePos.push_front(head);
    snakeObj.snakePos.pop_back();

    // Check if the snake's head has collided with its own body
    // If so, play the game-over sound and reset the game
    if (snakeObj.snakeBody.find(snakeObj.snakePos.front()) != snakeObj.snakeBody.end())
    {
        soundManager.playAudio("dead");
        resetGame();
    }
}

// Renders the game
void SnakeGame::render (const float& time)
{
	window.clear();
	renderGrid();

	if (interface.isMenu)
	{
		anim.scoreAnim(soundManager, scoreClock, Color::Red, score, Vector2f(interface.framePos.x + interface.frameObj.getGlobalBounds().width + 20, interface.framePos.y));
		interface.menu(menuClock);
	}
	else
	{
		if (colors.up)
		{
			anim.explodeFood(foodObj.isHit, Color(0, 255, 0, 150), lastFoodPos, time);
			foodObj.setFillColor(Color(0, 255, 0));
		}
		else if (colors.right)
		{
			anim.explodeFood(foodObj.isHit, Color(0, 255, 255, 150), lastFoodPos, time);
			foodObj.setFillColor(Color(0, 255, 255));
		}
		else if (colors.down)
		{
			anim.explodeFood(foodObj.isHit, Color(255, 255, 0, 150), lastFoodPos, time);
			foodObj.setFillColor(Color(255, 255, 0));
		}
		else if (colors.left)
		{
			anim.explodeFood(foodObj.isHit, Color(255, 165, 0, 150), lastFoodPos, time);
			foodObj.setFillColor(Color(255, 165, 0));
		}
		renderSnake();
		window.draw(foodObj);
	}

	window.display();
}

// Render the grid with different colors
void SnakeGame::renderGrid ()
{
	Color color;

	if (interface.isMenu)
	{
		color.a = 40;
	} else
	{
		color.a = 100;
	}
	if (colors.up)
	{
		color.g = 255;
	}
	else if (colors.right)
	{
		color.g = 255;
		color.b = 255;
	}
	else if (colors.down)
	{
		color.r = 255;
		color.g = 255;
	}
	else if (colors.left)
	{
		color.r = 255;
		color.g = 165;
	}

	for (unsigned int i = 0; i < winGrid.winX; ++i)
	{
		if (i % winGrid.scale == 0)
		{
			Vertex line[2] = {
				Vertex(Vector2f(i, winGrid.scale), color),
				Vertex(Vector2f(i, winGrid.winY - winGrid.scale), color)
			};
			window.draw(line, 2, Lines);
		}
	}

	for (unsigned int i = 0; i < winGrid.winY; ++i)
	{
		if (i % winGrid.scale == 0)
		{
			Vertex line[2] {
				Vertex(Vector2f(winGrid.scale, i), color),
				Vertex(Vector2f(winGrid.winX - winGrid.scale, i), color)
			};
			window.draw(line, 2, Lines);
		}
	}
}

// Renders the snake object
void SnakeGame::renderSnake ()
{
        const Vector2f& head = snakeObj.snakePos.front();
        const Vector2f& food = foodObj.getPosition();

        if (head.x == food.x && head.y == food.y)
        {
                ++score;
                foodObj.isHit = true;
                soundManager.playAudio("food");
                snakeObj.increment();
                lastFoodPos = foodObj.getPosition();
                foodObj.setRandomPosition(snakeObj);
                clock.restart();
        }

        for (Vector2f& pos: snakeObj.snakePos)
        {
                RectangleShape shape{Vector2f(winGrid.scale, winGrid.scale)};

                if (colors.up)          shape.setFillColor(Color(0, 255, 0, 200));
                else if (colors.right)  shape.setFillColor(Color(0, 255, 255, 200));
                else if (colors.down)   shape.setFillColor(Color(255, 255, 0, 200));
                else if (colors.left)   shape.setFillColor(Color(255, 165, 0, 200));

                shape.setPosition(pos);
                window.draw(shape);
        }

        Text text(intToStr(score), font);
        text.setFillColor(Color::Red);
        text.setPosition(head.x + winGrid.scale * 2, head.y - winGrid.scale * 2);

        window.draw(text);
}

void SnakeGame::resetGame ()
{
        menuClock.restart();
        scoreClock.restart();
        anim.total = 0;
        anim.scoreOnce = false;
        anim.pitch = 0.1;
        interface.isMenu = true;
        colors = {true, false, false, false};
        foodObj.setFillColor(Color(0, 255, 0));
        foodObj.setRandomPosition(snakeObj);
        foodObj.isHit = false;
        snakeObj.isMoving = false;
        snakeObj.snakePos.clear();
        snakeObj.snakeBody.clear();
        snakeObj.dir = {false, false, false, true};
        snakeObj.initHeadPos(winGrid.scale, winGrid.scale);
}

