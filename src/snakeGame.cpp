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

// snakeGame class constructor
snakeGame::snakeGame (const unsigned int winX,
                      const unsigned int winY,
                      const char* windowTitle)
:   score       (0),
    isRunning   (true),
    colors      {true, false, false, false},
    winGrid     (winX,
                 winY),
    foodObj     (sf::Vector2f(20.0f, 20.0f),
                 winGrid.scale),
    window      (sf::VideoMode(winX, winY),
                 windowTitle),
    introduction(&window),
    anim        (&window,
                 winGrid.scale),
    interface   (&window) {
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
    return;
}

// Handles events of the game
void snakeGame::events () {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::LostFocus) {
            snakeObj.isMoving = false;
        } else if (event.type == sf::Event::GainedFocus) {
            snakeObj.isMoving = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
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
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
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
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (snakeObj.isMoving &&
                !snakeObj.dir.left &&
                !snakeObj.dir.right) {
                soundManager.playAudio("snake");
                snakeObj.dir = {false, false, true, false};
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (snakeObj.isMoving &&
                !snakeObj.dir.right &&
                !snakeObj.dir.left) {
                soundManager.playAudio("snake");
                snakeObj.dir = {false, false, false, true};
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
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
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (!interface.isMenu) {
                soundManager.playAudio("quit");
                anim.total = 0;
                score = 0;
                resetGame();
                interface.isMenu = true;
            }
        }
    }
    return;
}

// Handles updates of the game
void snakeGame::updates () {
    if (snakeObj.isMoving) {
        snakeObj.movement(winGrid.scale);
    }
    return;
}

// Renders the game
void snakeGame::render (float time) {
    window.clear();
    renderGrid();
    if (interface.isMenu) {
        anim.scoreAnim(soundManager, scoreClock, sf::Color::Red, score, sf::Vector2f(490, 90));
        interface.menu(menuClock);
    } else {
        if (colors.up) {
            anim.explodeFood(foodObj.isHit, sf::Color(0, 255, 0, 150), lastFoodPos, time);
            foodObj.setFillColor(sf::Color(0, 255, 0));
        } else if (colors.right) {
            anim.explodeFood(foodObj.isHit, sf::Color(0, 255, 255, 150), lastFoodPos, time);
            foodObj.setFillColor(sf::Color(0, 255, 255));
        } else if (colors.down) {
            anim.explodeFood(foodObj.isHit, sf::Color(255, 255, 0, 150), lastFoodPos, time);
            foodObj.setFillColor(sf::Color(255, 255, 0));
        } else if (colors.left) {
            anim.explodeFood(foodObj.isHit, sf::Color(255, 165, 0, 150), lastFoodPos, time);
            foodObj.setFillColor(sf::Color(255, 165, 0));
        }
        renderSnake();
        window.draw(foodObj);
    }

    window.display();
    return;
}

// Render the grid with different colors
void snakeGame::renderGrid () {
    std::vector<line> vertLines = winGrid.getVertLines();
    std::vector<line> horiLines = winGrid.getHoriLines();
    sf::Color color;
    if (colors.up) {
        color = sf::Color(0, 255, 0, 150);
    } else if (colors.right) {
        color = sf::Color(0, 255, 255, 150);
    } else if (colors.down) {
        color = sf::Color(255, 255, 0, 150);
    } else if (colors.left) {
        color = sf::Color(255, 165, 0, 150);
    }
    for (unsigned int i = 0; i < (unsigned int)vertLines.size(); i++) {
        sf::Vertex l[2] {
            sf::Vertex(sf::Vector2f(vertLines[i]._p1.x, vertLines[i]._p1.y), color),
            sf::Vertex(sf::Vector2f(vertLines[i]._p2.x, vertLines[i]._p2.y), color)
        };
        window.draw(l, 2, sf::Lines);
    }
    for (unsigned int i = 0; i < (unsigned int)horiLines.size(); i++) {
        sf::Vertex l[2] {
            sf::Vertex(sf::Vector2f(horiLines[i]._p1.x, horiLines[i]._p1.y), color),
            sf::Vertex(sf::Vector2f(horiLines[i]._p2.x, horiLines[i]._p2.y), color)
        };
        window.draw(l, 2, sf::Lines);
    }
    return;
}

// Renders the snake object
void snakeGame::renderSnake () {
    snakeRects.clear();
    for (unsigned int i = 0; i < snakeObj.snakePos.size(); i++) {
        sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(winGrid.scale, winGrid.scale));
        if (colors.up) {
            shape->setFillColor(sf::Color(0, 255, 0, 200));
        } else if (colors.right) {
            shape->setFillColor(sf::Color(0, 255, 255, 200));
        } else if (colors.down) {
            shape->setFillColor(sf::Color(255, 255, 0, 200));
        } else if (colors.left) {
            shape->setFillColor(sf::Color(255, 165, 0, 200));
        }
        if (snakeObj.snakePos[i].x < 20) {
            colors = {false, false, false, true};
            soundManager.playAudio("portal");
            snakeObj.snakePos[i].x = 600;
        } else if (snakeObj.snakePos[i].x > 600) {
            colors = {false, true, false, false};
            soundManager.playAudio("portal");
            snakeObj.snakePos[i].x = 20;
        } else if (snakeObj.snakePos[i].y < 20) {
            colors = {true, false, false, false};
            soundManager.playAudio("portal");
            snakeObj.snakePos[i].y = 440;
        } else if (snakeObj.snakePos[i].y > 440) {
            colors = {false, false, true, false};
            soundManager.playAudio("portal");
            snakeObj.snakePos[i].y = 20;
        }
        shape->setPosition(snakeObj.snakePos[i]);
        snakeRects.push_back(*shape);
        delete shape;
    }
    for (unsigned int i = 0; i < snakeRects.size(); i++) {
        if (i < snakeRects.size()-1 &&
            snakeRects.back().getGlobalBounds().intersects(snakeRects[i].getGlobalBounds())) {
            soundManager.playAudio("dead");
            resetGame();
        } else if (snakeRects.back().getGlobalBounds().intersects(foodObj.getGlobalBounds())) {
            score+=1;
            foodObj.isHit = true;
            soundManager.playAudio("food");
            snakeObj.increment();
            lastFoodPos = foodObj.getPosition();
            foodObj.setRandomPosition();
            clock.restart();
        } else {
            window.draw(snakeRects[i]);
        }
    }
    sf::Font font;
    font.loadFromFile("november.ttf");
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Red);
    text.setPosition(snakeRects.back().getPosition().x + 50, snakeRects.back().getPosition().y - 20);
    text.setString(interface.intToStr(score));
    window.draw(text);
    return;
}

void snakeGame::resetGame () {
    menuClock.restart();
    scoreClock.restart();
    anim.total = 0;
    anim.scoreOnce = false;
    anim.pitch = 0.1;
    interface.isMenu = true;
    colors = {true, false, false, false};
    foodObj.setFillColor(sf::Color(0, 255, 0));
    foodObj.setRandomPosition();
    snakeObj.isMoving = false;
    foodObj.isHit = false;
    snakeObj.snakePos.clear();
    snakeObj.dir = {false, false, false, true};
    snakeObj.initHeadPos(winGrid.scale, winGrid.scale);
    return;
}
