#include "Game.h"

// Private functions
void Game::initVariables()
{
    // Initialize game variables
    this->window = nullptr;
}
void Game::initWindow()
{
    // Initialize the window
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    this->window = new sf::RenderWindow(this->videoMode, "Little Ghost", sf::Style::Titlebar | sf::Style::Close);
}


// Constructor and Destructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
}
Game::~Game()
{
    delete this->window; //avoid memory leak
}

// Accessors
const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}




//Functions
void Game::pollEvents()
{
    // event polling
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }

}
void Game::update()
{
    /*
        Update game logic (keyboard inputs, character movement, etc.)
    */

    // event polling
    this->pollEvents();
}
void Game::render()
{
    /*
        -clear old frame
        -render object
        -display frame in window

        Renders the game objects.
    */

    this->window->clear(sf::Color(255,0,0));

    //Draw game

    this->window->display();

}