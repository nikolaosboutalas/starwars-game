#pragma once

#include "movinggameobject.h"
#include <string>

using namespace std;

class Player : public MovingGameObject {

	float last_time_shot;

public:

	Player(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed);
	virtual ~Player();
	
	void update() override;
	void draw() override;

};