#ifndef ANIM_H
#define ANIM_H

#include <SFML/Graphics.hpp>
#include "sound.h"

// anim class for creating animations
class Anim {
    public:
        unsigned int    scale;
        unsigned int    total;
        float           pitch;
        bool            scoreOnce;
    public:
        Anim (sf::RenderWindow*, unsigned int);
    public:
        void explodeFood (bool&, sf::Color, sf::Vector2f, float);
        void scoreAnim (SoundManager&, sf::Clock&, sf::Color, unsigned int, sf::Vector2f);
    private:
        std::string intToStr (int);
    private:
        sf::RenderWindow*   window;
        sf::Color           color;
        // explodeFood
        sf::RectangleShape  shape1;
        sf::RectangleShape  shape2;
        sf::RectangleShape  shape3;
        sf::RectangleShape  shape4;
        // scoreAnim
        sf::Text            text;
        sf::Font            font;
};

#endif
