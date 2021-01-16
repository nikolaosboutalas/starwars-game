#pragma once

#include "movinggameobject.h"

class Kamikaze : public MovingGameObject {

public:

	Kamikaze(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed);
	virtual ~Kamikaze();
	
	void update() override;
	void draw() override;

};