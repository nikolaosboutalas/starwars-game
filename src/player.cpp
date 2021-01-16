#include "config.h"
#include "graphics.h"
#include "player.h"
#include "movinggameobject.h"
#include "game.h"
#include "shot.h"

#include <string>

using namespace std;

Player::Player(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed) : MovingGameObject(pos_x, pos_y, size_x, size_y, orientation, texture, speed){
	
    last_time_shot = graphics::getGlobalTime();

}

Player::~Player(){

}

void Player::update(){

	MovingGameObject::update();

	float pos_y = this -> getPosY();
	float pos_x = this -> getPosX();
	float speed = this -> getSpeed();

	float temp_pos;

	if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP)){
        temp_pos = pos_y - speed * graphics::getDeltaTime();
        if(temp_pos > WINDOW_HEIGHT/2 + 50) pos_y = temp_pos;
    }
    if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN)){
        temp_pos = pos_y + speed * graphics::getDeltaTime();
        if(temp_pos < WINDOW_HEIGHT - 50) pos_y = temp_pos;
    }
    if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT)){
        temp_pos = pos_x - speed * graphics::getDeltaTime();
        if(temp_pos > 50) pos_x = temp_pos;
    }
    if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT)){
		temp_pos = pos_x + speed * graphics::getDeltaTime();
        if(temp_pos < WINDOW_WIDTH - 50) pos_x = temp_pos;
    }

    this -> setPosX(pos_x);
    this -> setPosY(pos_y);

    if(graphics::getGlobalTime() > last_time_shot + 500){

        if (graphics::getKeyState(graphics::SCANCODE_SPACE)){

            Game * game = reinterpret_cast<Game *>(graphics::getUserData());
            game -> addObject(new Shot(pos_x + 3 , pos_y - 60, 100, 100, this -> getOrientation(), "shot", 1));
            last_time_shot = graphics::getGlobalTime();
        }
    }
}

void Player::draw(){

	MovingGameObject::draw();

	float pos_y = this -> getPosY();
	float pos_x = this -> getPosX();

	graphics::Brush br;
    br.outline_opacity = 0.0f;
	int exhaust_number = (int)(graphics::getGlobalTime()/100) % 4 + 1;
	br.texture = string(ASSET_PATH) + "exhaust" + to_string(exhaust_number) + ".png";

	graphics::setOrientation(this -> getOrientation());
	graphics::drawRect(pos_x-5, pos_y+50, 30, 30, br);
	graphics::drawRect(pos_x+8, pos_y+50, 30, 30, br);
	graphics::resetPose();

}