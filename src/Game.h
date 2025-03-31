
#ifndef GAME_H
#define GAME_H

//precompiled headers
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

/*
Class that acts as a game engine
Wrapper Class
*/

class Game
{
    private:
        //Variables
        //Window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;
        

        //Private functions
        void initVariables();
        void initWindow();

    public:
        // Constructor and Destructor
        Game();
        virtual ~Game();

        // Accessors
        const bool getWindowIsOpen() const;

        //Functions
        void pollEvents();
        void update();
        void render();
};


#endif // GAME_H