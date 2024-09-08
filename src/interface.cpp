#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include <string>
#include "interface.hpp"
#include "constants.hpp"
#include "anim.hpp"

using std::cout;
using std::endl;
using std::string;
using sf::Vector2f;
using sf::Color;
using sf::RenderWindow;
using sf::Clock;
using constants::FONT_FILENAME;
using constants::WINDOW_SIZEX;
using constants::WINDOW_SIZEY;
using constants::FAILED_TO_LOAD_FILE_ERR;

// Interface Text Class
interfaceText::interfaceText (const string& filepath, const string& str, int charSize, Color color)
{
    if (!font.loadFromFile(filepath))
        throw std::runtime_error(FAILED_TO_LOAD_FILE_ERR + " '" + filepath + "'");

    setFillColor(color);
    setFont(font);
    setCharacterSize(charSize);
    setString(str);
}

// Interface Class
Interface::Interface (RenderWindow* window)
    // Interface Class Members's Initialization
:   isMenu(true),
    menuSelect(1),
    window(window),

    // Frame Object
    frameObj        (Vector2f(WINDOW_SIZEX/2, WINDOW_SIZEY/2)),
    framePos        (WINDOW_SIZEX/2 - frameObj.getGlobalBounds().width/2,
                     WINDOW_SIZEY/2 - frameObj.getGlobalBounds().height/2),

    // Menu Interface Objects
    title           (FONT_FILENAME, "CYBERSERPENT", 42, Color::Green),
    developer       (FONT_FILENAME, "By zEuS0390", 32, Color::Green),
    play            (FONT_FILENAME, "PLAY", 32, Color(0, 255, 0)),
    exit            (FONT_FILENAME, "EXIT", 32, Color(0, 255, 0)),

    menuGroupPos    (framePos.x + frameObj.getGlobalBounds().width/2,
                     framePos.y + frameObj.getGlobalBounds().height/2 -
                     (title.getGlobalBounds().height +
                     developer.getGlobalBounds().height +
                     play.getGlobalBounds().height +
                     exit.getGlobalBounds().height)),

    titlePos(menuGroupPos.x - title.getGlobalBounds().width/2, menuGroupPos.y + 20),
    devPos(menuGroupPos.x - developer.getGlobalBounds().width/2, menuGroupPos.y + 70),
    playPos(menuGroupPos.x - play.getGlobalBounds().width/2, menuGroupPos.y + 140),
    exitPos(menuGroupPos.x - exit.getGlobalBounds().width/2, menuGroupPos.y + 180)
{
}

void Interface::menu (Clock& clock)
{
    frame();
    frameSelect.setFillColor(Color(0, 150, 0, 150));

    switch (menuSelect)
    {
        case 1:
            frameSelect.setSize(Vector2f(frameObj.getGlobalBounds().width, play.getGlobalBounds().height + 10));
            frameSelect.setPosition(Vector2f(framePos.x, playPos.y));
            break;
        case 2:
            frameSelect.setSize(Vector2f(frameObj.getGlobalBounds().width, exit.getGlobalBounds().height + 10));
            frameSelect.setPosition(Vector2f(framePos.x, exitPos.y));
            break;
    }
    window->draw(frameSelect);

    float time = clock.getElapsedTime().asSeconds();
    if (time >= 0.5f && time < 1.5f)
    {
        color = Color::Green;
        title.setFillColor(color);
        developer.setFillColor(color);
        play.setFillColor(color);
        exit.setFillColor(color);
    }
    else if (time >= 1.5f)
    {
        color = Color::Yellow;
        title.setFillColor(color);
        developer.setFillColor(color);
        play.setFillColor(color);
        exit.setFillColor(color);
        clock.restart();
    }

    developer.setPosition(devPos);
    title.setPosition(titlePos);
    play.setPosition(playPos);
    exit.setPosition(exitPos);

    window->draw(title);
    window->draw(developer);
    window->draw(play);
    window->draw(exit);
}

void Interface::frame ()
{
    frameObj.setFillColor(Color(0, 75, 0));
    frameObj.setPosition(framePos);
    window->draw(frameObj);
}

