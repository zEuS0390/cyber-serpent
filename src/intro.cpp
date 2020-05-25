#include <SFML/Graphics.hpp>
#include <iostream>
#include "intro.h"

intro::intro (sf::RenderWindow* renderWin)
:   addVal(0.9f),
    alpha(0),
    fadeIn(true),
    fadeOut(false),
    isSFML(true),
    isCreator(false),
    isRunning(true),
    renderWin(renderWin) {
    renderWin->setMouseCursorVisible(false);
}

void intro::init (void) {
    if (!sfmlLogo.loadFromFile("gfx/SFML_Logo.png")) {
        return;
    }
    if (!creatorLogo.loadFromFile("gfx/Creator_Logo.png")) {
        return;
    }
    renderWin->setFramerateLimit(120);
    texture.loadFromImage(sfmlLogo);
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255, 255, 255, alpha));
    loop();
    return;
}

void intro::updates (void) {
    if (fadeIn) {
        if (isSFML) {
            if (alpha <= 255) {
                alpha += addVal;
            } else {
                fadeIn = false;
                fadeOut = true;
            }
        } else if (isCreator) {
            if (alpha <= 255) {
                alpha += addVal;
            } else {
                fadeIn = false;
                fadeOut = true;
            }
        }
        clock.restart();
    } else if (clock.getElapsedTime().asSeconds() >= 1.0f && fadeOut) {
        if (isSFML) {
            if (alpha >= 0) {
                alpha -= addVal;
            } else {
                texture.loadFromImage(creatorLogo);
                isCreator = true;
                isSFML = false;
                fadeIn = true;
                fadeOut = false;
            }
        } else if (isCreator) {
            if (alpha >= 0) {
                alpha -= addVal;
            } else {
                isRunning = false;
                isCreator = false;
                fadeOut = false;
            }
        }
    }
    sprite.setColor(sf::Color(255, 255, 255, alpha));
    return;
}

void intro::events (void) {
    sf::Event event;
    while (renderWin->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                isRunning = false;
        }
    }
    return;
}

void intro::renders (void) {
    renderWin->clear();
    renderWin->draw(sprite);
    renderWin->display();
    return;
}

void intro::loop (void) {
    while (isRunning) {
        events();
        updates();
        renders();
    }
    return;
}
