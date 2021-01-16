#include "shot.h"
#include "graphics.h"
#include "config.h"

using namespace std;

Shot::Shot(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed) : MovingGameObject(pos_x, pos_y, size_x, size_y, orientation, texture, speed){
    
    graphics::playSound(string(ASSET_PATH) +  this -> getTexture() + ".mp3", 0.5f, false);

}

Shot::~Shot(){
	
}

void Shot::update(){

	MovingGameObject::update();
	
	float pos_y = this -> getPosY();
	float speed = this -> getSpeed();

	pos_y -= speed * graphics::getDeltaTime();

	this -> setPosY(pos_y);

}