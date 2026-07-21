#include "Game.h"

// ----------------------------------------------------------------------------------
// Program entry point: creates a Game object, runs setup, then starts the game loop.
// ----------------------------------------------------------------------------------
int main()
{
    Game game;           
    game.setup();        
    game.run();
    return 0;
}