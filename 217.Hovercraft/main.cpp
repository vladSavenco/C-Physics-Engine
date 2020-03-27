#include "GameEngine.h"

int main()
{
    GameEngine gameEngine("HoverCraft", 1920, 1080, 4, 6, false);

    //Main loop
    while(!gameEngine.GetWindowShouldClose())
    {
        //Update input--
        gameEngine.update();
        gameEngine.render();
    }
    return 0;
}