#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "interface.h"
#include "anim.h"

// Interface Text Class
interfaceText::interfaceText (std::string filepath,
                              std::string str,
                              int charSize,
                              sf::Color color) {
    if (!font.loadFromFile(filepath)) {
        std::cout << "Error loading font file." << std::endl;
    } else {
        setFillColor(color);
        setFont(font);
        setCharacterSize(charSize);
        setString(str);
    }
}

// Interface Class
Interface::Interface (sf::RenderWindow* window)
:
    // Interface Class Members's Initialization
    isMenu(true),
    menuSelect(1),
    window(window),

    // Frame Object
    frameObj(sf::Vector2f(300.0f, 300.0f)),
    framePos(170.0f, 90.0f),

    // Menu Interface Objects
    frameSelect (sf::Vector2f(200, 50)),
    title ("november.ttf", "SNAKE-GAME", 50, sf::Color::Green),
    developer ("november.ttf", "By zEuS-0390", 35, sf::Color::Green),
    play ("november.ttf", "PLAY", 40, sf::Color(0, 255, 0)),
    exit ("november.ttf", "EXIT", 40, sf::Color(0, 255, 0)),
    titlePos ((640/2)-title.getGlobalBounds().width/2, 100),
    devPos ((640/2)-developer.getGlobalBounds().width/2, 160),
    playPos (640/2-play.getGlobalBounds().width/2, 240),
    exitPos ((640/2)-(exit.getGlobalBounds().width/2), 320) {
}

void Interface::menu (sf::Clock& clock) {
    frame();

    frameSelect.setFillColor(sf::Color(0, 150, 0, 150));

    if (menuSelect == 1) {
        frameSelect.setPosition(sf::Vector2f(220, 238));
    } else if (menuSelect == 2) {
        frameSelect.setPosition(sf::Vector2f(220, 318));
    }
    window->draw(frameSelect);

    float time = clock.getElapsedTime().asSeconds();
    if (time >= 0.5f && time < 1.5f) {
        color = sf::Color::Green;
        title.setFillColor(color);
        developer.setFillColor(color);
        play.setFillColor(color);
        exit.setFillColor(color);
    } else if (time >= 1.5f) {
        color = sf::Color::Yellow;
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
    return;
}

std::string Interface::intToStr (int number) {
    std::stringstream str;
    str << number;
    std::string s = str.str();
    return s;
}

void Interface::frame () {
    frameObj.setFillColor(sf::Color(0, 75, 0));
    frameObj.setPosition(framePos);
    window->draw(frameObj);
    return;
}
