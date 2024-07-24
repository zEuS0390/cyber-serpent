#include <SFML/Graphics.hpp>
#include <iostream>
#include "intro.hpp"

using sf::RenderWindow;
using sf::Color;
using sf::Event;
using sf::Keyboard;

intro::intro (RenderWindow* renderWin)
:   addVal(0.9f),
    alpha(0),
    fadeIn(true),
    fadeOut(false),
    isSFML(true),
    isCreator(false),
    isRunning(true),
    renderWin(renderWin) 
{
    renderWin->setMouseCursorVisible(false);
}

void intro::init () 
{
    if (!sfmlLogo.loadFromFile("gfx/SFML_Logo.png"))
        return;

    if (!creatorLogo.loadFromFile("gfx/Creator_Logo.png"))
        return;

    renderWin->setFramerateLimit(250);
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
            } else 
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
    while (renderWin->pollEvent(event)) 
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
    renderWin->clear();
    renderWin->draw(sprite);
    renderWin->display();
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
