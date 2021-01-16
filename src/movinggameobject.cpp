#include "movinggameobject.h"
#include "gameobject.h"

#include <string>

using namespace std;

MovingGameObject::MovingGameObject(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed) : GameObject(pos_x, pos_y, size_x, size_y, orientation, texture){
	this -> speed = speed;
}

MovingGameObject::~MovingGameObject(){
	
}

float MovingGameObject::getSpeed(){
	return this -> speed;
}