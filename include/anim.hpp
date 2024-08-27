#ifndef ANIM_HPP
#define ANIM_HPP

#include <SFML/Graphics.hpp>
#include "sound.hpp"

using sf::RenderWindow;
using sf::Color;
using sf::Vector2f;
using sf::Clock;

// anim class for creating animations
class Anim {
public:
	unsigned int		scale;
        unsigned int		total;
        float			pitch;
        bool			scoreOnce;
        Anim			(RenderWindow&, unsigned int);
        void explodeFood	(bool&, Color, Vector2f, const float&);
        void scoreAnim		(SoundManager&, Clock&, Color, unsigned int, Vector2f);
    private:
        sf::RenderWindow&       window;
        sf::Color		color;
        // explodeFood
        sf::RectangleShape	shape1;
        sf::RectangleShape	shape2;
        sf::RectangleShape	shape3;
        sf::RectangleShape	shape4;
        // scoreAnim
        sf::Text		text;
        sf::Font		font;
};

#endif

