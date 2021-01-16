#include "game.h"
#include "graphics.h"
#include "config.h"
#include "player.h"
#include "gameobject.h"
#include "enemy.h"
#include "kamikaze.h"
#include "explosion.h"
#include "shot.h"

#include <cmath>
#include <ctime>
#include <random>

using namespace std;

Game::Game(){

	graphics::setFont(string(ASSET_PATH) + "font.otf");
	graphics::playMusic(string(ASSET_PATH) + "menu.mp3", 0.1f, true, 0);

	last_enemy_spawn_time = 0;
	last_kamikaze_spawn_time = 0;
	game_state = 0;
	object_counter = 0;
	pressed_space = 0;

}

Game::~Game(){

}

void Game::update(){

	switch(game_state){
    	case 0:
    		updateStartScreen();
    		break;
    	case 1:
    		updateGame();
    		break;
    	case 2:
    		updateGameOverScreen();
    		break;
    }
}

void Game::draw(){

	graphics::Brush br;
    br.texture = std::string(ASSET_PATH) + "background.png";
    br.outline_opacity = 0.0f;
    float offset = fmod(graphics::getGlobalTime(), WINDOW_HEIGHT);

    graphics::drawRect(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + offset, WINDOW_WIDTH, WINDOW_HEIGHT, br);
    graphics::drawRect(WINDOW_WIDTH/2, -WINDOW_HEIGHT/2 + offset, WINDOW_WIDTH, WINDOW_HEIGHT, br);

    switch(game_state){
    	case 0:
    		drawStartScreen();
    		break;
    	case 1:
    		drawGame();
    		break;
    	case 2:
    		drawGameOverScreen();
    		break;
    }

}

void Game::addObject(GameObject * object){
	game_objects[object_counter] = object;
	object_counter++;
}

void Game::updateStartScreen(){

	if (graphics::getKeyState(graphics::SCANCODE_SPACE) && graphics::getGlobalTime() > pressed_space + 200){

		game_state = 1;
		game_time_started = graphics::getGlobalTime();
		player = new Player(WINDOW_WIDTH/2, WINDOW_HEIGHT*3/4, 100, 100, 90, "ship", 0.7f);

	}
	
}

void Game::drawStartScreen(){

	graphics::Brush br;
	br.fill_color[0] = 1.f;
	br.fill_color[1] = 1.f;
	br.fill_color[2] = 0.f;

	graphics::drawText(140, 100, 40, "Star Wars", br);

	br.fill_opacity = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/200);
	graphics::drawText(130, WINDOW_HEIGHT-100, 20, "Press SPACE to start", br);

	br.texture = string(ASSET_PATH) + "ship.png";
	br.outline_opacity = 0.f;
	br.fill_opacity = 1.0f;
	br.fill_color[2] = 1.f;
	graphics::drawRect(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 200, 200, br);

}

void Game::updateGame(){

	score = ( graphics::getGlobalTime() - game_time_started )/100 ;

	if(graphics::getGlobalTime() > last_enemy_spawn_time + max(3000 - score, 1000)){

	    srand((unsigned int)time(NULL));	
		addObject(new Enemy(rand() % 400 + 50, 0 , 70, 70, -90, "enemy", 0.3f));
		last_enemy_spawn_time = graphics::getGlobalTime();

	}

	if(graphics::getGlobalTime() > last_kamikaze_spawn_time + max(5000 - score, 2000)){

    	srand((unsigned int)time(NULL));	
		int temp_a[2] = {1 ,-1};
		int temp_n = temp_a[rand() % 2];
		addObject(new Kamikaze(250 - temp_n * 400, player -> getPosY(), 100, 100, temp_n * 180, "kamikaze", temp_n * 0.3f));
		last_kamikaze_spawn_time = graphics::getGlobalTime();

	}

	for(int i=0;i<object_counter;++i){

		if(game_objects[i] -> collidable()){

			if(checkCollision(player, game_objects[i])){

				player -> setTerminate(true);
				addObject(new Explosion(player -> getPosX(), player -> getPosY(), player -> getSizeX(), player -> getSizeY()));
				game_objects[i] -> setTerminate(true);
				addObject(new Explosion(game_objects[i] -> getPosX(), game_objects[i] -> getPosY(), game_objects[i] -> getSizeX(), game_objects[i] -> getSizeY()));
			
			}
		}	
	}

	for(int i=0;i<object_counter;++i){

		for(int j=i+1;j<object_counter;++j){

			if(game_objects[i] -> collidable() && game_objects[j] -> collidable()){

				if(checkCollision(game_objects[i], game_objects[j])){

					game_objects[i] -> setTerminate(true);
					addObject(new Explosion(game_objects[i] -> getPosX(), game_objects[i] -> getPosY(), game_objects[i] -> getSizeX(), game_objects[i] -> getSizeY()));
					game_objects[j] -> setTerminate(true);
					addObject(new Explosion(game_objects[j] -> getPosX(), game_objects[j] -> getPosY(), game_objects[j] -> getSizeX(), game_objects[j] -> getSizeY()));
				
				}
			
			}	
		
		}
	
	}

	for(int i=0;i<object_counter;++i){

		if(game_objects[i] -> getTerminate()){

			delete game_objects[i];
			game_objects[i] = nullptr;
			game_objects[i] = game_objects[--object_counter];

		}

		else game_objects[i] -> update();

	}

	if(player -> getTerminate()){

		delete player;

		for(int i=0;i<object_counter;++i) delete game_objects[i];

		object_counter = 0;
		game_state = 2;

	    srand((unsigned int)time(NULL));


		graphics::playSound(string(ASSET_PATH) + to_string(rand()%2) + ".mp3", 1.0f, false);


	}
	else player -> update();

}

void Game::drawGame(){

	graphics::Brush br;
	br.fill_color[0] = 1.f;
	br.fill_color[1] = 1.f;
	br.fill_color[2] = 0.f;

	graphics::drawText(WINDOW_WIDTH/2 - 60, WINDOW_HEIGHT - 50, 25, "Score: " + to_string(score), br);

	for(int i=0;i<object_counter;++i) game_objects[i] -> draw();

	player -> draw();

}

void Game::updateGameOverScreen(){
	if (graphics::getKeyState(graphics::SCANCODE_SPACE)){
		game_state = 0;
		pressed_space = graphics::getGlobalTime();
	}
}

void Game::drawGameOverScreen(){

	graphics::Brush br;
	br.fill_color[0] = 1.f;
	br.fill_color[1] = 1.f;
	br.fill_color[2] = 0.f;

	graphics::drawText(110, 200, 50, "Game Over", br);
	graphics::drawText(170, 400, 30, "Score: "+ to_string(score) , br);

	br.fill_opacity = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/200);
	graphics::drawText(130, WINDOW_HEIGHT-100, 20, "Press SPACE to restart", br);


}

bool Game::checkCollision(GameObject * ob1, GameObject * ob2){

	float pos_x1, pos_y1;
	float pos_x2, pos_y2;

	pos_x1 = ob1 -> getPosX();
	pos_y1 = ob1 -> getPosY();
	pos_x2 = ob2 -> getPosX();
	pos_y2 = ob2 -> getPosY();

	if(sqrt( pow(pos_x1 - pos_x2, 2) +  pow(pos_y1 - pos_y2, 2) ) < (ob1 -> getRadius() + ob2 -> getRadius())/2) return true;
	
	return false;
	
}