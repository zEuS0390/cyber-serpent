#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "interface.hpp"
#include "anim.hpp"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using sf::Vector2f;
using sf::Color;
using sf::RenderWindow;
using sf::Clock;

// Interface Text Class
interfaceText::interfaceText (string filepath,
                              string str,
                              int charSize,
                              Color color) 
{
	if (!font.loadFromFile(filepath)) 
	{
		cout << "Error loading font file." << endl;
	} 
	else 
	{
		setFillColor(color);
		setFont(font);
		setCharacterSize(charSize);
		setString(str);
	}
}

// Interface Class
Interface::Interface (RenderWindow* window)
:
	// Interface Class Members's Initialization
	isMenu(true),
	menuSelect(1),
	window(window),

	// Frame Object
	frameObj(Vector2f(350.0f, 300.0f)),
	framePos(145.0f, 90.0f),

	// Menu Interface Objects
	frameSelect (Vector2f(200, 50)),
	title ("november.ttf", "CYBER SERPENT", 50, Color::Green),
	developer ("november.ttf", "By zEuS0390", 35, Color::Green),
	play ("november.ttf", "PLAY", 40, Color(0, 255, 0)),
	exit ("november.ttf", "EXIT", 40, Color(0, 255, 0)),
	titlePos ((640/2)-title.getGlobalBounds().width/2, 100),
	devPos ((640/2)-developer.getGlobalBounds().width/2, 160),
	playPos (640/2-play.getGlobalBounds().width/2, 240),
	exitPos ((640/2)-(exit.getGlobalBounds().width/2), 320) 
{
}

void Interface::menu (Clock& clock) 
{
	frame();

	frameSelect.setFillColor(Color(0, 150, 0, 150));

	switch (menuSelect) 
	{
		case 1:
			frameSelect.setPosition(Vector2f(220, 238));
			break;
		case 2:
			frameSelect.setPosition(Vector2f(220, 318));
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

string Interface::intToStr (int number) 
{
	stringstream str;
	str << number;
	string s = str.str();
	return s;
}

void Interface::frame () 
{
	frameObj.setFillColor(Color(0, 75, 0));
	frameObj.setPosition(framePos);
	window->draw(frameObj);
}
