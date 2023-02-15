#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "anim.h"
#include "sound.h"

Anim::Anim (sf::RenderWindow* window, unsigned int scale)
:   scale(scale),
    total(0),
    pitch(0.1f),
    scoreOnce(false),
    window(window),
    shape1(sf::Vector2f(scale, scale)),
    shape2(sf::Vector2f(scale, scale)),
    shape3(sf::Vector2f(scale, scale)),
    shape4(sf::Vector2f(scale, scale)) {
}

void Anim::explodeFood (bool& isActive,
                        sf::Color color,
                        sf::Vector2f foodPos,
                        float time) {

    color = color;

    if (isActive) {
        sf::Vector2f shape1Pos(foodPos.x + scale, foodPos.y);
        shape1.setFillColor(color);
        shape1.setPosition(shape1Pos);

        sf::Vector2f shape2Pos(foodPos.x - scale, foodPos.y);
        shape2.setFillColor(color);
        shape2.setPosition(shape2Pos);

        sf::Vector2f shape3Pos(foodPos.x, foodPos.y + scale);
        shape3.setFillColor(color);
        shape3.setPosition(shape3Pos);

        sf::Vector2f shape4Pos(foodPos.x, foodPos.y - scale);
        shape4.setFillColor(color);
        shape4.setPosition(shape4Pos);

        if (time >= 0.05f) {
            if (time >= 0.05f &&
                time < 0.5f) {
                window->draw(shape1);
                window->draw(shape2);
                window->draw(shape3);
                window->draw(shape4);
            }
            if (time >= 0.5f &&
                time < 1.0f) {
                shape1.setPosition(sf::Vector2f(shape1.getPosition().x + scale, shape1.getPosition().y));
                shape2.setPosition(sf::Vector2f(shape2.getPosition().x - scale, shape2.getPosition().y));
                shape3.setPosition(sf::Vector2f(shape3.getPosition().x, shape3.getPosition().y + scale));
                shape4.setPosition(sf::Vector2f(shape4.getPosition().x, shape4.getPosition().y - scale));
                window->draw(shape1);
                window->draw(shape2);
                window->draw(shape3);
                window->draw(shape4);
            }
            if (time >= 1.0f &&
                time < 1.5f){
                shape1.setPosition(sf::Vector2f(shape1.getPosition().x + 2*scale, shape1.getPosition().y));
                shape2.setPosition(sf::Vector2f(shape2.getPosition().x - 2*scale, shape2.getPosition().y));
                shape3.setPosition(sf::Vector2f(shape3.getPosition().x, shape3.getPosition().y + 2*scale));
                shape4.setPosition(sf::Vector2f(shape4.getPosition().x, shape4.getPosition().y - 2*scale));
                window->draw(shape1);
                window->draw(shape2);
                window->draw(shape3);
                window->draw(shape4);
            }
            if(time >= 1.5f) {
                isActive = false;
            }

        }
    }
    return;
}

void Anim::scoreAnim (SoundManager& soundManager,
                      sf::Clock& clock,
                      sf::Color color,
                      unsigned int score,
                      sf::Vector2f position) {
    float time = clock.getElapsedTime().asSeconds();
    if (time >= 1.0f) {
        scoreOnce = true;
    }
    if (scoreOnce && score > 0) {
        if (time >= 0.09f && total < score) {
            soundManager.setPitch("blip", pitch);
            soundManager.playAudio("blip");
            total += 1;
            clock.restart();
            if (pitch <= 2.0) {
                pitch+=0.1;
            }
        }
        if (!font.loadFromFile("november.ttf")) {
            return;
        }
        text.setCharacterSize(60);
        text.setFont(font);
        text.setFillColor(color);
        text.setString(intToStr(total));
        text.setPosition(position);
        window->draw(text);
    }
    return;
}

std::string Anim::intToStr (int number) {
    std::stringstream str;
    str << number;
    std::string s = str.str();
    return s;
}
