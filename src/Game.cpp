#include "Game.h"

// Private functions
void Game::initVariables()
{
    // Initialize game variables
    this->window = nullptr;

    //Game logic
    this->points=0;
    this->enemySpawnTimerMax=1000.f;
    this->enemySpawnTimer=this->enemySpawnTimerMax; 
    this->maxEnemies=5;
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
    this->enemy.setPosition(10.f, 10.f);
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

void Game::spawnEnemy()
{
    /*
        @return void

        Spawns enemies end sets thier color and positions.
        -Sets a random postion.
        -Sets a random color.
        -Adss enemy to the vector.

    */
   this->enemy.setPosition(
        static_cast<float>(rand()%static_cast<int>(this->window->getSize().x-this->enemy.getSize().x)),
        0.f
   );
   //static_cast<float>(...) =>turn this value safely into a float
   //rand => takes integers

   this->enemy.setFillColor(sf::Color::Red);

   //spawns the enemy
   this->enemies.push_back(this->enemy);

   //Remove enemies at end of screen
   
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

void Game::updateMousePositions()
{
    /*
    @return void

    Updates the mouse positions:
    - mouse position relative to the window (vector2i = vector of 2 integers)
    */

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);

}

void Game::updateEnemies()
{
    /*
        @return void

        Updates the enemy spawntimer and spawn enemies
        when the total amount of enemies is smaller than the maximum.
        Moves the enemies downwards.
        Removes the enemies at the edge of the screens //TODO

     */


    //Updating the timer for enemy spawning
    if(this->enemies.size()<this->maxEnemies)
    {
        if(this->enemySpawnTimer>=this->enemySpawnTimerMax)
        {
            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer=0.f;
        }
        else
            this->enemySpawnTimer+=1.f;

    }

    //Move the enemies
    for(auto &e : this->enemies)
    {
        e.move(0.f,1.f);
    }
}


void Game::update()
{
    /*
        Update game logic (keyboard inputs, character movement, etc.)
    */

    this->pollEvents();

    this->updateMousePositions();

    this->updateEnemies();

   
}
void Game::renderEnemies()
{
    //rendering all the enemies
    for(auto &e : this->enemies)
    {
        this->window->draw(e);
    }

}
void Game::render()
{
    /*
        @return void

        -clear old frame
        -render object
        -display frame in window

        Renders the game objects.
    */

    this->window->clear();

    //Draw game objects
    this->renderEnemies();

    this->window->display();
}