#include "Game.h"

// Private functions
void Game::initVariables()
{
    // Initialize game variables
    this->window = nullptr;

    //Game logic
    this->endGame=false;  
    this->points=0;
    this->health=10; 
    this->enemySpawnTimerMax=10.f;
    this->enemySpawnTimer=this->enemySpawnTimerMax; 
    this->maxEnemies=6;
    this->mouseHeld=false;
}

void Game::initWindow()
{
    // Initialize the window
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    this->window = new sf::RenderWindow(this->videoMode, "Little Ghost", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60); // Set the frame rate limit 
}

void Game::initFonts()
{
    if(this->font.loadFromFile("resources/fonts/Dosis.ttf"))
    {
        std::cout<<"Font loaded!"<<std::endl;
    }
    else
    {
        std::cout<<"ERROR::GAME::INITFONS:: Error loading font!"<<std::endl;
    }  
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(20);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setStyle(sf::Text::Bold);
    this->uiText.setString("NONE");    
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Blue);
    // this->enemy.setOutlineThickness(1.f);
}



// Constructor and Destructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
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

const bool Game::getEndGame() const
{
    return this->endGame;
}



//Functions
void Game::spawnEnemy()
{
    /*
        @return void

        Spawns enemies end sets thier types, colors. Spawns them at random position .
        -Sets a random type (diff)
        -Sets a random postion.
        -Sets a random color.
        -Adss enemy to the vector.

    */
   this->enemy.setPosition(
        static_cast<float>(rand()%static_cast<int>(this->window->getSize().x-this->enemy.getSize().x)),
        0.f
   );
    //static_cast<float>(...) => turn this value safely into a float
   //rand => only takes integers


   //Randomise enemy type 
   int type=rand()%5;

   switch(type)
   {
        case 0:
            this->enemy.setFillColor(sf::Color::Magenta);
            this->enemy.setSize(sf::Vector2f(10.f, 10.f));
            break;
        case 1:
            this->enemy.setFillColor(sf::Color::Red);
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            break;
        case 2:
            this->enemy.setFillColor(sf::Color::Yellow);
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            break;
        case 3:
            this->enemy.setFillColor(sf::Color::Blue);
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            break;
        case 4:
            this->enemy.setFillColor(sf::Color::Green);
            this->enemy.setSize(sf::Vector2f(80.f, 90.f));
            break;
        default:
            this->enemy.setFillColor(sf::Color::White);
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            break;
   }

   //Spawns the enemy
   this->enemies.push_back(this->enemy);

   //Remove enemies at end of screen
}


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
    - mouse position relative to the view (vector2f = vector of 2 floats)
    */

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
   this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    /*
    @return void
    Updates the text that is displayed on the screen:
    - Points (number of enemies killed)
    - Health (number of enemies that passed the screen)
    */
    std::stringstream ss;

    ss << "Points: " << this->points << "\n"
       << "Health: " << this->health << "\n";

    this->uiText.setString(ss.str());
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

    //Moving and updating the enemies
    for(int i=0;i<this->enemies.size();++i)
    {
        bool deleted=false;

        //move the enemy
        this->enemies[i].move(0.f,1.f);

        //check if the enemy is past the bottom of the screen
        if(this->enemies[i].getPosition().y>this->window->getSize().y)
        { 
            this->enemies.erase(this->enemies.begin()+i);
            this->health-=1;
            std::cout<<"Health: "<<this->health<<std::endl;
        }
    }

    //check if clicked uppon
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(this->mouseHeld==false)
        {
            this->mouseHeld=true;
            bool deleted=false;

            for(size_t i=0;i<this->enemies.size() && deleted==false;++i)
            {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    
                    //Gain points
                    if(this->enemies[i].getFillColor()==sf::Color::Magenta)
                    {
                        this->points+=100;
                        this->health+=1;
                    }
                    else if(this->enemies[i].getFillColor()==sf::Color::Red)
                        this->points+=100;
                    else if(this->enemies[i].getFillColor()==sf::Color::Yellow)
                        this->points+=50;
                    else if(this->enemies[i].getFillColor()==sf::Color::Blue)
                        this->points+=25;
                    else if(this->enemies[i].getFillColor()==sf::Color::Green)
                        this->points+=10;
                    std::cout<<"Points: "<<this->points<<std::endl;


                    //Delete the enemy
                    deleted=true;
                    this->enemies.erase(this->enemies.begin()+i);
                }
            }
        } 
    }
    else
    {
        this->mouseHeld=false;
    }
}

void Game::update()
{
    /*
        Update game logic (keyboard inputs, character movement, etc.)
    */

    this->pollEvents();

    if(this->endGame==false)
    {
        this->updateMousePositions();

        this->updateText(); 

        this->updateEnemies();
    }

    //End game condition
    if(this->health<=0)
    {
        this->endGame=true;
        std::cout<<"Game Over!"<<std::endl;
    }

}


void Game::renderText(sf::RenderTarget& target) 
{
    target.draw(this->uiText); 
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    //rendering all the enemies
    for(auto &e : this->enemies)
    {
        target.draw(e);
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
    this->renderEnemies(*this->window);
 
    this->renderText(*this->window);

    this->window->display();
}