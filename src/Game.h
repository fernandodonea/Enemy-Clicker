
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

        //Mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;
  
        //Game logic
        bool endGame;
        unsigned points;
        int health;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        unsigned maxEnemies;
        bool mouseHeld;

        //Game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;
        

        //Private functions
        void initVariables();
        void initWindow();
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
        void updateEnemies();
        void update();
        void renderEnemies();
        void render();
};


#endif // GAME_H