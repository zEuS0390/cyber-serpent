#ifndef INTERFACE_H
#define INTERFACE_H

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
class interfaceText : public Text {
    public:
        interfaceText (string, string, int, Color);
    private:
        Font font;
};

// interface class
class Interface {
    public:
        bool isMenu;
        int menuSelect;
    public:
        Interface (RenderWindow*);
    public:
        void check (string);
        void menu (Clock&);
        void option (int);
        string intToStr (int);
    private:
        void frame ();
    private:
        RenderWindow*   window;
        Color           color;
        // Frame Object
        RectangleShape  frameObj;
        Vector2f        framePos;
        // Highlight Select Object
        RectangleShape  frameSelect;
        // Menu Interface Objects
        interfaceText       title;
        interfaceText       developer;
        interfaceText       play;
        interfaceText       exit;
        Vector2f        titlePos;
        Vector2f        devPos;
        Vector2f        playPos;
        Vector2f        exitPos;
};

#endif
