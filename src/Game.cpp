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

    this->window->setFramerateLimit(60); // Set the frame rate limit 
}

void Game::initEnemies()
{
    this->enemy.setPosition(400.f, 300.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Red);
    this->enemy.setOutlineColor(sf::Color::Blue);
    this->enemy.setOutlineThickness(1.f);
}

// Constructor and Destructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
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
            //Close window 
            case sf::Event::Closed:
                this->window->close();
                break;
            //Close window when esc is pressed
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

    // Update mouse position
    //relative to the screen
    //  std::cout<<"Mouse pos: "<<sf::Mouse::getPosition().x<<", "<<sf::Mouse::getPosition().y<<std::endl;
    //relative to the window
    std::cout<<"Mouse pos: "<<sf::Mouse::getPosition(*this->window).x<<", "<<sf::Mouse::getPosition(*this->window).y<<std::endl;

    //
}
void Game::render()
{
    /*
        -clear old frame
        -render object
        -display frame in window

        Renders the game objects.
    */

    this->window->clear();

    //Draw game
    this->window->draw(this->enemy);

    this->window->display();
}