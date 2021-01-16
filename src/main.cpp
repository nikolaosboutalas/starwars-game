#include "graphics.h"
#include "game.h"
#include "config.h"

void update(float ms){

    Game * game = reinterpret_cast<Game *>(graphics::getUserData());
    game -> update();

}

void draw(){

    Game * game = reinterpret_cast<Game *>(graphics::getUserData());
    game -> draw();

}
 
int main()
{
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Star Wars Episode 0: Return of the Developer");
    graphics::setCanvasSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    Game game;
    graphics::setUserData(&game);
    
    graphics::startMessageLoop();
 
    return 0;
}
