#pragma once

#include "movinggameobject.h"

using namespace std;

class Shot : public MovingGameObject {

public:

	Shot(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture, float speed);
	virtual ~Shot();
	
	void update();

};