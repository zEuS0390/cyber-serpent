#ifndef INTERFACE_H
#define INTERFACE_H
#include <SFML/Graphics.hpp>
#include <string>

// interfaceText class (inherits sf::Text class)
class interfaceText : public sf::Text {
    public:
        interfaceText (std::string,
                       std::string,
                       int,
                       sf::Color);
    private:
        sf::Font font;
};

// interface class
class interface {
    public:
        bool isMenu;
        int menuSelect;
    public:
        interface (sf::RenderWindow*);
    public:
        void check (std::string);
        void menu (sf::Clock&);
        void option (int);
        std::string intToStr (int);
    private:
        void frame (void);
    private:
        sf::RenderWindow*   window;
        sf::Color           color;
        // Frame Object
        sf::RectangleShape  frameObj;
        sf::Vector2f        framePos;
        // Highlight Select Object
        sf::RectangleShape  frameSelect;
        // Menu Interface Objects
        interfaceText       title;
        interfaceText       developer;
        interfaceText       play;
        interfaceText       exit;
        sf::Vector2f        titlePos;
        sf::Vector2f        devPos;
        sf::Vector2f        playPos;
        sf::Vector2f        exitPos;
};

#endif
