#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <string>

using std::string;
using sf::Text;
using sf::Color;
using sf::Font;
using sf::RenderWindow;
using sf::Clock;
using sf::RectangleShape;
using sf::Vector2f;

// interfaceText class (inherits sf::Text class)
class interfaceText : public Text 
{
public:
        interfaceText (const string&, const string&, int, Color);
private:
        Font font;
};

// interface class
class Interface 
{
public:
        bool isMenu;
        int menuSelect;
	Interface			(RenderWindow*);
	void check			(string);
	void menu			(Clock&);
	// Frame Object
	RectangleShape			frameObj;
	Vector2f			framePos;
private:
        RenderWindow*			window;
        Color				color;
        // Highlight Select Object
        RectangleShape			frameSelect;
        // Menu Interface Objects
        interfaceText			title;
        interfaceText			developer;
        interfaceText			play;
        interfaceText			exit;
	Vector2f			menuGroupPos;
        Vector2f        		titlePos;
        Vector2f        		devPos;
        Vector2f        		playPos;
        Vector2f        		exitPos;
	void frame ();
};

#endif
