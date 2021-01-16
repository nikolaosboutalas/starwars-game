#pragma once

#include "gameobject.h"

class Explosion : public GameObject {

	float time;

public:

	Explosion(float pos_x, float pos_y, float size_x, float size_y);
	virtual ~Explosion();

	void update() override;
	void draw() override;

	bool collidable() override;
	
};