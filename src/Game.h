
#ifndef GAME_H
#define GAME_H

//precompiled headers
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

/*
Class that acts as a game engine
Wrapper Class
*/

class Game
{
    private:
        /*Variables*/

        //Window
        sf::RenderWindow* window;
        sf::VideoMode video_mode;
        sf::Event ev;

        //Mouse positions
        sf::Vector2i mouse_pos_window;
        sf::Vector2f mouse_pos_view;

        //Resources
        sf::Font font;

        //Text
        sf::Text ui_text;
  
        //Game logic
        bool end_game;
        unsigned points;
        int health;

        float enemy_spawn_timer;
        float enemy_spawn_timer_max;
        unsigned max_enemies;

        bool  mouse_held;

        //Game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;
        

        //Private functions
        void initVariables();
        void initWindow();
        void initFonts();
        void initText(); 
        void initEnemies();

    public:
        // Constructor and Destructor
        Game();
        virtual ~Game();

        // Accessors
        const bool getWindowIsOpen() const;
        const bool getEndGame() const;

        //Functions
        void spawnEnemy();

        void pollEvents();

        void updateMousePositions();
        void updateText();
        void updateEnemies();
        void update();
   
        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render();
};


#endif // GAME_H