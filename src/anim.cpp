#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include "anim.hpp"
#include "utils.hpp"
#include "sound.hpp"
#include "constants.hpp"

using std::string;
using sf::RenderWindow;
using constants::FONT_FILENAME;
using constants::FAILED_TO_LOAD_FILE_ERR;
using sf::Vector2f;
using sf::Color;
using sf::Clock;

Anim::Anim (RenderWindow& window, unsigned int scale)
:
	scale(scale),
	total(0),
	pitch(0.1f),
	scoreOnce(false),
	window(window),
	shape1(Vector2f(scale, scale)),
	shape2(Vector2f(scale, scale)),
	shape3(Vector2f(scale, scale)),
	shape4(Vector2f(scale, scale))
{
        if (!font.loadFromFile(FONT_FILENAME))
                throw std::runtime_error(FAILED_TO_LOAD_FILE_ERR + " '" + FONT_FILENAME + "'");
}

void Anim::explodeFood (bool& isActive, Color color, Vector2f foodPos, const float& time)
{
        color = color;

        if (!isActive)
                return;

        Vector2f shape1Pos(foodPos.x + scale, foodPos.y);
        shape1.setFillColor(color);
        shape1.setPosition(shape1Pos);

        Vector2f shape2Pos(foodPos.x - scale, foodPos.y);
        shape2.setFillColor(color);
        shape2.setPosition(shape2Pos);

        Vector2f shape3Pos(foodPos.x, foodPos.y + scale);
        shape3.setFillColor(color);
        shape3.setPosition(shape3Pos);

        Vector2f shape4Pos(foodPos.x, foodPos.y - scale);
        shape4.setFillColor(color);
        shape4.setPosition(shape4Pos);

        if (time >= 0.05f)
        {
                if (time >= 0.05f && time < 0.5f)
                {
                        window.draw(shape1);
                        window.draw(shape2);
                        window.draw(shape3);
                        window.draw(shape4);
                }
                if (time >= 0.5f && time < 1.0f)
                {
                        shape1.setPosition(Vector2f(shape1.getPosition().x + scale, shape1.getPosition().y));
                        shape2.setPosition(Vector2f(shape2.getPosition().x - scale, shape2.getPosition().y));
                        shape3.setPosition(Vector2f(shape3.getPosition().x, shape3.getPosition().y + scale));
                        shape4.setPosition(Vector2f(shape4.getPosition().x, shape4.getPosition().y - scale));
                        window.draw(shape1);
                        window.draw(shape2);
                        window.draw(shape3);
                        window.draw(shape4);
                }
                if (time >= 1.0f && time < 1.5f)
                {
                        shape1.setPosition(Vector2f(shape1.getPosition().x + 2 * scale, shape1.getPosition().y));
                        shape2.setPosition(Vector2f(shape2.getPosition().x - 2 * scale, shape2.getPosition().y));
                        shape3.setPosition(Vector2f(shape3.getPosition().x, shape3.getPosition().y + 2 * scale));
                        shape4.setPosition(Vector2f(shape4.getPosition().x, shape4.getPosition().y - 2 * scale));
                        window.draw(shape1);
                        window.draw(shape2);
                        window.draw(shape3);
                        window.draw(shape4);
                }
                if(time >= 1.5f)
                        isActive = false;
        }
}

void Anim::scoreAnim (SoundManager& soundManager, Clock& clock, Color color, unsigned int score, Vector2f position)
{
        float time = clock.getElapsedTime().asSeconds();

        if (time >= 1.0f)
                scoreOnce = true;

        if (scoreOnce && score > 0)
        {
                if (time >= 0.09f && total < score)
                {
                        soundManager.setPitch("blip", pitch);
                        soundManager.playAudio("blip");
                        total += 1;
                        clock.restart();
                        if (pitch <= 2.0)
                                pitch+=0.1;
                }
                text.setCharacterSize(32);
                text.setFont(font);
                text.setFillColor(color);
                text.setString(intToStr(total));
                text.setPosition(position);
                window.draw(text);
        }
}

