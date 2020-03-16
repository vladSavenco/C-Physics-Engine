#include "GameEngine.h"

int main()
{
    GameEngine gameEngine("Vlad_Engine", 640, 480, 4, 6, false);

    //Main loop
    while(!gameEngine.GetWindowShouldClose())
    {
        //Update input--
        gameEngine.update();
        gameEngine.render();
    }
    return 0;
}