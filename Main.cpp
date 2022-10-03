#include<iostream>
#include"Game.h"
int main()
{
    //init srand
    std::srand(static_cast<unsigned>(time(NULL)));

   //init Game Engine
    Game game;

    //Game Loop
    while (game.running() && !game.getEndGame()){
       
        //Update
        game.update();
        //Render
        game.render();
        
        
    }
    
    //end of application
    return 0;
 }