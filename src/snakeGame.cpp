#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "windowGrid.h"
#include "snakeGame.h"
#include "interface.h"
#include "snake.h"
#include "sound.h"
#include "anim.h"
#include "constants.h"

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
        foodObj.setRandomPosition();
        mainLoop();
}

// Main loop of the game
void snakeGame::mainLoop () {
	window.setFramerateLimit(10);
	while (isRunning) {
		float time = clock.getElapsedTime().asSeconds();
		updates();
		events();
		render(time);
	}
}

// Handles events of the game
void snakeGame::events () {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
		    window.close();
		} else if (event.type == Event::LostFocus) {
		    snakeObj.isMoving = false;
		} else if (event.type == Event::GainedFocus) {
		    snakeObj.isMoving = true;
		} else if (Keyboard::isKeyPressed(Keyboard::Up) ||
			   Keyboard::isKeyPressed(Keyboard::W)) {
		    if (snakeObj.isMoving &&
			!snakeObj.dir.up &&
			!snakeObj.dir.down) {
			soundManager.playAudio("snake");
			snakeObj.dir = {true, false, false, false};
		    } else if (interface.isMenu) {
			if (interface.menuSelect > 1) {
			    interface.menuSelect -= 1;
			soundManager.playAudio("button_up");
			}
		    }
		} else if (Keyboard::isKeyPressed(Keyboard::Down) ||
			   Keyboard::isKeyPressed(Keyboard::S)) {
		    if (snakeObj.isMoving &&
			!snakeObj.dir.down &&
			!snakeObj.dir.up) {
			soundManager.playAudio("snake");
			snakeObj.dir = {false, true, false, false};
		    } else if (interface.isMenu) {
			if (interface.menuSelect < 2) {
			    interface.menuSelect += 1;
			    soundManager.playAudio("button_down");
			}
		    }
		} else if (Keyboard::isKeyPressed(Keyboard::Left) ||
			   Keyboard::isKeyPressed(Keyboard::A)) {
		    if (snakeObj.isMoving &&
			!snakeObj.dir.left &&
			!snakeObj.dir.right) {
			soundManager.playAudio("snake");
			snakeObj.dir = {false, false, true, false};
		    }
		} else if (Keyboard::isKeyPressed(Keyboard::Right) ||
			   Keyboard::isKeyPressed(Keyboard::D)) {
		    if (snakeObj.isMoving &&
			!snakeObj.dir.right &&
			!snakeObj.dir.left) {
			soundManager.playAudio("snake");
			snakeObj.dir = {false, false, false, true};
		    }
		} else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		    if (interface.isMenu) {
			if (interface.menuSelect == 1) {
			    soundManager.playAudio("button_enter");
			    interface.isMenu = false;
			    snakeObj.isMoving = true;
			    score = 0;
			} else if (interface.menuSelect == 2) {
			    isRunning = false;
			}
		    }
		} else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		    if (!interface.isMenu) {
			soundManager.playAudio("quit");
			anim.total = 0;
			score = 0;
			resetGame();
			interface.isMenu = true;
		    }
		}
	}
}

// Handles updates of the game
void snakeGame::updates () {
	if (!snakeObj.isMoving) return;

	Vector2f head = snakeObj.snakePos.back();

	if (snakeObj.dir.up)	head.y -= winGrid.scale;
	if (snakeObj.dir.down)	head.y += winGrid.scale;
	if (snakeObj.dir.left)	head.x -= winGrid.scale;
	if (snakeObj.dir.right)	head.x += winGrid.scale;

	snakeObj.snakePos.insert(snakeObj.snakePos.end(), head);
	snakeObj.snakePos.erase(snakeObj.snakePos.begin());

	for (int i = 0; i < snakeObj.snakePos.size()-1; ++i) {
		if (snakeObj.snakePos.back() == snakeObj.snakePos[i]) {
			soundManager.playAudio("dead");
			resetGame();
		}
	}
}

// Renders the game
void snakeGame::render (float time) {
	window.clear();
	renderGrid();
	if (interface.isMenu) {
		anim.scoreAnim(soundManager, scoreClock, Color::Red, score, Vector2f(510, 90));
		interface.menu(menuClock);
	} else {
		if (colors.up) {
			anim.explodeFood(foodObj.isHit, Color(0, 255, 0, 150), lastFoodPos, time);
			foodObj.setFillColor(Color(0, 255, 0));
		} else if (colors.right) {
			anim.explodeFood(foodObj.isHit, Color(0, 255, 255, 150), lastFoodPos, time);
			foodObj.setFillColor(Color(0, 255, 255));
		} else if (colors.down) {
			anim.explodeFood(foodObj.isHit, Color(255, 255, 0, 150), lastFoodPos, time);
			foodObj.setFillColor(Color(255, 255, 0));
		} else if (colors.left) {
			anim.explodeFood(foodObj.isHit, Color(255, 165, 0, 150), lastFoodPos, time);
			foodObj.setFillColor(Color(255, 165, 0));
		}
		renderSnake();
		window.draw(foodObj);
	}

	window.display();
}

// Render the grid with different colors
void snakeGame::renderGrid () {
	Color color;

	if (colors.up)
		color = Color(0, 255, 0, 150);
	else if (colors.right)
		color = Color(0, 255, 255, 150);
	else if (colors.down)
		color = Color(255, 255, 0, 150);
	else if (colors.left)
		color = Color(255, 165, 0, 150);

	for (int i = 0; i < winGrid.winX; ++i) {
		if (i % winGrid.scale == 0) {
			Vertex line[2] = {
				Vertex(Vector2f(i, winGrid.scale), color),
				Vertex(Vector2f(i, winGrid.winY-winGrid.scale), color)
			};
			window.draw(line, 2, Lines);
		}
	}

	for (int i = 0; i < winGrid.winY; ++i) {
		if (i % winGrid.scale == 0) {
			Vertex line[2] {
				Vertex(Vector2f(winGrid.scale, i), color),
				Vertex(Vector2f(winGrid.winX - winGrid.scale, i), color)
			};
			window.draw(line, 2, Lines);
		}
	}
}

// Renders the snake object
void snakeGame::renderSnake () {

	for (unsigned int i = 0; i < snakeObj.snakePos.size(); i++) {
		RectangleShape shape(Vector2f(winGrid.scale, winGrid.scale));

		if (colors.up)
			shape.setFillColor(Color(0, 255, 0, 200));
		else if (colors.right)
			shape.setFillColor(Color(0, 255, 255, 200));
		else if (colors.down)
			shape.setFillColor(Color(255, 255, 0, 200));
		else if (colors.left)
			shape.setFillColor(Color(255, 165, 0, 200));

		float& snake_posx = snakeObj.snakePos[i].x;
		float& snake_posy = snakeObj.snakePos[i].y;

		if (snakeObj.snakePos[i].x < winGrid.scale) {
			colors = {false, false, false, true};
			soundManager.playAudio("portal");
			snake_posx = winGrid.winX - winGrid.scale * 2;
		} else if (snakeObj.snakePos[i].x > winGrid.winX - winGrid.scale * 2) {
			colors = {false, true, false, false};
			soundManager.playAudio("portal");
			snake_posx = winGrid.scale;
		} else if (snakeObj.snakePos[i].y < winGrid.scale) {
			colors = {true, false, false, false};
			soundManager.playAudio("portal");
			snake_posy = winGrid.winY - winGrid.scale * 2;
		} else if (snakeObj.snakePos[i].y > winGrid.winY - winGrid.scale * 2) {
			colors = {false, false, true, false};
			soundManager.playAudio("portal");
			snake_posy = winGrid.scale;
		}

		shape.setPosition(snakeObj.snakePos[i]);
		window.draw(shape);
	}

	if (snakeObj.snakePos.back().x == foodObj.getPosition().x && snakeObj.snakePos.back().y == foodObj.getPosition().y) {
		++score;
		foodObj.isHit = true;
		soundManager.playAudio("food");
		snakeObj.increment();
		lastFoodPos = foodObj.getPosition();
		foodObj.setRandomPosition();
		clock.restart();
	}

	Text text;
	text.setFont(font);
	text.setFillColor(Color::Red);
	// text.setPosition(snakeObj.snakePos.back().x + 50, snakeObj.snakePos.back().y - 20);
	text.setPosition(snakeObj.snakePos.back().x + winGrid.scale * 2, snakeObj.snakePos.back().y - winGrid.scale * 2);
	text.setString(interface.intToStr(score));
	window.draw(text);
}

void snakeGame::resetGame () {
	menuClock.restart();
	scoreClock.restart();
	anim.total = 0;
	anim.scoreOnce = false;
	anim.pitch = 0.1;
	interface.isMenu = true;
	colors = {true, false, false, false};
	foodObj.setFillColor(Color(0, 255, 0));
	foodObj.setRandomPosition();
	snakeObj.isMoving = false;
	foodObj.isHit = false;
	snakeObj.snakePos.clear();
	snakeObj.dir = {false, false, false, true};
	snakeObj.initHeadPos(winGrid.scale, winGrid.scale);
}
