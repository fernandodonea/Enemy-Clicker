#include "game.h"


int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init game engine
    EnemyClicker::Game game;
    
    //Game loop
    while (game.GetWindowIsOpen() && !game.GetEndGame())
    {
        //Update
        game.Update();

        //Render
        game.Render();
          
    }

    //End of application
    return 0;


}