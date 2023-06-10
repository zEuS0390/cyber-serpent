#ifndef INTRO_H
#define INTRO_H
#include <SFML/Graphics.hpp>

class intro {
    public:
        float               addVal;
        float               alpha;
        bool                fadeIn;
        bool                fadeOut;
        bool                isSFML;
        bool                isCreator;
        bool                isRunning;
    public:
        intro               (sf::RenderWindow*);
    public:
        void init           ();
        void updates        ();
        void events         ();
        void renders        ();
        void loop           ();
    private:
        sf::Clock           clock;
        sf::RenderWindow*   renderWin;
        sf::Image           sfmlLogo;
        sf::Image           creatorLogo;
        sf::Texture         texture;
        sf::Sprite          sprite;
};

#endif
