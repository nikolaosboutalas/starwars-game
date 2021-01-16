#include "config.h"
#include "graphics.h"
#include "gameobject.h"

#include <string>

using namespace std;

GameObject::GameObject(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture){
	this -> pos_x = pos_x;
	this -> pos_y = pos_y;
	this -> size_x = size_x;
	this -> size_y = size_y;
	this -> orientation = orientation;
	this -> texture = texture;
	terminate = false;
}

GameObject::~GameObject(){

}

void GameObject::update(){

	if((pos_x < 0 - WINDOW_WIDTH) || (pos_x > WINDOW_WIDTH*2) || (pos_y < 0 - WINDOW_HEIGHT) || (pos_y > WINDOW_HEIGHT*2)) terminate = true;

}

void GameObject::draw(){

	graphics::Brush br;
    br.outline_opacity = 0.0f;
	br.texture = string(ASSET_PATH) + texture + ".png";

	graphics::setOrientation(orientation);
	graphics::drawRect(pos_x, pos_y, size_x, size_y, br);
	graphics::resetPose();
}

float GameObject::getPosX(){
	return pos_x;
}

float GameObject::getPosY(){
	return pos_y;
}

float GameObject::getSizeX(){
	return size_x;
}

float GameObject::getSizeY(){
	return size_y;
}

float GameObject::getOrientation(){
	return orientation;
}

float GameObject::getRadius(){
	return (size_y + size_x)/4;
}

bool GameObject::getTerminate(){
	return terminate;
}

string GameObject::getTexture(){
	return texture;
}

void GameObject::setPosX(float pos_x){
	this -> pos_x = pos_x;
}

void GameObject::setPosY(float pos_y){
	this -> pos_y = pos_y;
}

void GameObject::setTerminate(bool terminate){
	this -> terminate = terminate;
}

bool GameObject::collidable(){
	return true;
}