#pragma once

#include "movinggameobject.h"

class Enemy : public MovingGameObject {

	float last_time_shot;
	float final_pos;

public:

	Enemy(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed);
	virtual ~Enemy();
	
	void update() override;
	void draw() override;

};