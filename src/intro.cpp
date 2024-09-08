#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include "intro.hpp"
#include "constants.hpp"

using sf::RenderWindow;
using sf::Color;
using sf::Event;
using sf::Keyboard;
using constants::IMAGE_SFML_LOGO;
using constants::IMAGE_CREATOR_LOGO;

intro::intro (RenderWindow& renderWin)
:   addVal(0.9f),
    alpha(0),
    fadeIn(true),
    fadeOut(false),
    isSFML(true),
    isCreator(false),
    isRunning(true),
    renderWin(renderWin)
{
    renderWin.setMouseCursorVisible(false);
    init();
}

void intro::init ()
{
    if (!sfmlLogo.loadFromFile(IMAGE_SFML_LOGO))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + IMAGE_SFML_LOGO + "'");

    if (!creatorLogo.loadFromFile(IMAGE_CREATOR_LOGO))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + IMAGE_CREATOR_LOGO + "'");

    renderWin.setFramerateLimit(250);
    texture.loadFromImage(sfmlLogo);
    sprite.setTexture(texture);
    sprite.setColor(Color(255, 255, 255, alpha));
    loop();
}

void intro::updates ()
{
    if (fadeIn)
    {
        if (isSFML)
        {
            if (alpha <= 255)
            {
                alpha += addVal;
            }
            else
            {
                fadeIn = false;
                fadeOut = true;
            }
        }
        else if (isCreator)
        {
            if (alpha <= 255)
            {
                alpha += addVal;
            }
            else
            {
                fadeIn = false;
                fadeOut = true;
            }
        }
        clock.restart();
    }
    else if (clock.getElapsedTime().asSeconds() >= 1.0f && fadeOut)
    {
        if (isSFML)
        {
            if (alpha >= 0)
            {
                alpha -= addVal;
            }
            else
            {
                texture.loadFromImage(creatorLogo);
                isCreator = true;
                isSFML = false;
                fadeIn = true;
                fadeOut = false;
            }
        }
        else if (isCreator)
        {
            if (alpha >= 0)
            {
                alpha -= addVal;
            }
            else
            {
                isRunning = false;
                isCreator = false;
                fadeOut = false;
            }
        }
    }
    sprite.setColor(Color(255, 255, 255, alpha));
}

void intro::events ()
{
    Event event;
    while (renderWin.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            isRunning = false;
        }
    }
}

void intro::renders ()
{
    renderWin.clear();
    renderWin.draw(sprite);
    renderWin.display();
}

void intro::loop ()
{
    while (isRunning)
    {
        events();
        updates();
        renders();
    }
}

