
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
        void _InitVariables();
        void _InitWindow();
        void _InitFonts();
        void _InitText(); 
        void _InitEnemies();

    public:
        // Constructor and Destructor
        Game();
        virtual ~Game();

        // Accessors
        const bool GetWindowIsOpen() const;
        const bool GetEndGame() const;

        //Functions
        void SpawnEnemy();

        void PollEvents();

        void UpdateMousePositions();
        void UpdateText();
        void UpdateEnemies();
        void Update();
   
        void RenderText(sf::RenderTarget& target);
        void RenderEnemies(sf::RenderTarget& target);
        void Render();
};


#endif // GAME_H