#include "kamikaze.h"
#include "config.h"
#include "graphics.h"
#include <random>
#include <ctime>
using namespace std;

Kamikaze::Kamikaze(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed) : MovingGameObject(pos_x, pos_y, size_x, size_y, orientation, texture, speed){
    srand((unsigned int)time(NULL));	
}

Kamikaze::~Kamikaze(){

}

void Kamikaze::update(){

	MovingGameObject::update();


	float pos_x = this -> getPosX();
	float speed = this -> getSpeed();

	pos_x += speed * graphics::getDeltaTime();
	this -> setPosX(pos_x);

}

void Kamikaze::draw(){

	MovingGameObject::draw();

	float pos_y = this -> getPosY();
	float pos_x = this -> getPosX();
	float orientation = this -> getOrientation();

	graphics::Brush br;
    br.outline_opacity = 0.0f;
	int exhaust_number = (int)(graphics::getGlobalTime()/100) % 4 + 1;
	br.texture = string(ASSET_PATH) + this -> getTexture() +"_exhaust" + to_string(exhaust_number) + ".png";

	graphics::setOrientation(orientation);
	if (orientation > 0 ) graphics::drawRect(pos_x-45, pos_y+1, 35, 35, br);
	else graphics::drawRect(pos_x+45, pos_y+1, 35, 35, br);
	graphics::resetPose();

}