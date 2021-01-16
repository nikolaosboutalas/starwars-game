#include "explosion.h"
#include "graphics.h"
#include "gameobject.h"
#include "config.h"
#include <iostream>

using namespace std;

Explosion::Explosion(float pos_x, float pos_y, float size_x, float size_y) : GameObject(pos_x, pos_y, size_x, size_y, 0.0f, "explosion1_"){
	
	time = graphics::getGlobalTime();
    graphics::playSound(string(ASSET_PATH) + "explosion1_.mp3", 0.5f, false);

}

Explosion::~Explosion(){

}

void Explosion::update(){

	if(graphics::getGlobalTime() - time > 550){

		this -> setTerminate(true);
	
	}
}

void Explosion::draw(){

	for(int i=1;i<12;++i){

		if(graphics::getGlobalTime() - time  > i * 50){

			graphics::Brush br;
			br.outline_opacity = 0.0f;
			br.texture = string(ASSET_PATH) + this -> getTexture() + to_string(i) + ".png";

			graphics::drawRect(this -> getPosX(), this -> getPosY(), this -> getSizeX(), this -> getSizeY(), br);

		}

	}

}

bool Explosion::collidable(){

	return false;

}