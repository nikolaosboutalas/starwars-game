#include "enemy.h"
#include "config.h"
#include "graphics.h"
#include "shot.h"
#include "game.h"
#include <random>
#include <ctime>
using namespace std;

Enemy::Enemy(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed) : MovingGameObject(pos_x, pos_y, size_x, size_y, orientation, texture, speed){
	
	last_time_shot = graphics::getGlobalTime();

    srand((unsigned int)time(NULL));	
	final_pos = rand() % 100;

}

Enemy::~Enemy(){

}

void Enemy::update(){

	MovingGameObject::update();

	float pos_y = this -> getPosY();
	float pos_x = this -> getPosX();
	float speed = this -> getSpeed();

	if(pos_y < 50 + final_pos){
		pos_y += speed * graphics::getDeltaTime();
		this -> setPosY(pos_y);
	}

	if(graphics::getGlobalTime() > last_time_shot + 2000){

    	Game * game = reinterpret_cast<Game *>(graphics::getUserData());
		game -> addObject(new Shot(pos_x , pos_y + 40, 80, 80, this -> getOrientation(), "enemy_shot", -0.5f));
        last_time_shot = graphics::getGlobalTime();
        
	}

}

void Enemy::draw(){

	MovingGameObject::draw();

	float pos_y = this -> getPosY();
	float pos_x = this -> getPosX();

	graphics::Brush br;
    br.outline_opacity = 0.0f;
	int exhaust_number = (int)(graphics::getGlobalTime()/100) % 4 + 1;
	br.texture = string(ASSET_PATH) + this -> getTexture() + "_exhaust" + to_string(exhaust_number) + ".png";

	graphics::setOrientation(this -> getOrientation());
	graphics::drawRect(pos_x+2, pos_y-50, 30, 30, br);
	graphics::resetPose();

}