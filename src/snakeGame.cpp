#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include "windowGrid.hpp"
#include "snakeGame.hpp"
#include "interface.hpp"
#include "constants.hpp"
#include "snake.hpp"
#include "sound.hpp"
#include "anim.hpp"

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
using std::next;

// snakeGame class constructor
snakeGame::snakeGame (const unsigned int winX,
                      const unsigned int winY,
                      const string& windowTitle)
:
	score		(0),
	isRunning	(true),
	colors      	{true, false, false, false},
	winGrid		(winX, winY),
	foodObj		(Vector2f(winGrid.scale, winGrid.scale), winGrid.scale),
	window		(VideoMode(winX, winY), windowTitle),
	introduction	(&window),
	anim		(&window, winGrid.scale),
	interface	(&window) 
{
	font.loadFromFile(FONT_FILENAME);
        introduction.init();
        window.setMouseCursorVisible(false);
        snakeObj.initHeadPos(winGrid.scale, winGrid.scale);
        mainLoop();
}

// Main loop of the game
void snakeGame::mainLoop () 
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
void snakeGame::events () 
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
				snakeObj.isMoving = false;
				break;
			case Event::GainedFocus:
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
void snakeGame::updates () 
{
	if (!snakeObj.isMoving) return;

	Vector2f head = snakeObj.snakePos.front();

	if (snakeObj.dir.up)	head.y -= winGrid.scale;
	if (snakeObj.dir.down)	head.y += winGrid.scale;
	if (snakeObj.dir.left)	head.x -= winGrid.scale;
	if (snakeObj.dir.right)	head.x += winGrid.scale;

	snakeObj.snakeBody.insert(snakeObj.snakePos.front());
	snakeObj.snakePos.push_front(head);
	Vector2f back = snakeObj.snakePos.back();
	snakeObj.snakeBody.erase(back);
	snakeObj.snakePos.pop_back();

	if (snakeObj.snakeBody.find(snakeObj.snakePos.front()) != snakeObj.snakeBody.end()) {
		soundManager.playAudio("dead");
		resetGame();
	}
}

// Renders the game
void snakeGame::render (const float& time) 
{
	window.clear();
	renderGrid();

	if (interface.isMenu) 
	{
		anim.scoreAnim(soundManager, scoreClock, Color::Red, score, Vector2f(510, 90));
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
void snakeGame::renderGrid () 
{
	Color color;

	if (colors.up)		color = Color(0, 255, 0, 150);
	else if (colors.right)	color = Color(0, 255, 255, 150);
	else if (colors.down)	color = Color(255, 255, 0, 150);
	else if (colors.left)	color = Color(255, 165, 0, 150);

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
void snakeGame::renderSnake () 
{
	for (Vector2f& pos: snakeObj.snakePos) {
		RectangleShape shape{Vector2f(winGrid.scale, winGrid.scale)};

		if (colors.up)		shape.setFillColor(Color(0, 255, 0, 200));
		else if (colors.right)	shape.setFillColor(Color(0, 255, 255, 200));
		else if (colors.down)	shape.setFillColor(Color(255, 255, 0, 200));
		else if (colors.left)	shape.setFillColor(Color(255, 165, 0, 200));

		if (pos.x < winGrid.scale) 
		{
			colors = {false, false, false, true};
			soundManager.playAudio("portal");
			pos.x = winGrid.winX - winGrid.scale * 2;
		} 
		else if (pos.x > winGrid.winX - winGrid.scale * 2) 
		{
			colors = {false, true, false, false};
			soundManager.playAudio("portal");
			pos.x = winGrid.scale;
		} 
		else if (pos.y < winGrid.scale) 
		{
			colors = {true, false, false, false};
			soundManager.playAudio("portal");
			pos.y = winGrid.winY - winGrid.scale * 2;
		} 
		else if (pos.y > winGrid.winY - winGrid.scale * 2) 
		{
			colors = {false, false, true, false};
			soundManager.playAudio("portal");
			pos.y = winGrid.scale;
		}

		shape.setPosition(pos);
		window.draw(shape);
	}

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

	Text text;
	text.setFont(font);
	text.setFillColor(Color::Red);
	text.setPosition(head.x + winGrid.scale * 2, head.y - winGrid.scale * 2);
	text.setString(interface.intToStr(score));

	window.draw(text);
}

void snakeGame::resetGame () 
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
