#pragma once

#include "gameobject.h"
#include <string>

using namespace std;

class MovingGameObject : public GameObject {

	float speed;

public:

	MovingGameObject(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed);
	virtual ~MovingGameObject();
	
	float getSpeed();
	
};